#ifndef SESSION_HPP
#define SESSION_HPP

#include <mutex>
#include <thread>
#include "alias_for_boost.h"
#include "users.h"
#include "command.h"


namespace myftp{

class Session
{
public:
    using Lock = std::unique_lock<std::mutex>;

    Session(Tcp::socket soc,
            const myftp::Users* users,
            std::mutex* m):
        socket_{std::move(soc)},
        user_table_{users},
        mutex_{m}
    {}

    void operator()()
    {
        do_session();
    }

private:
    Tcp::socket socket_;
    const myftp::Users* user_table_;
    std::mutex* mutex_;

    Lock lock() const
    {
        return Lock{*mutex_};
    }

    template<typename Printable>
    std::ostream& print_safely(const Printable& to_print) const
    {
        auto this_scope = lock();
        return  std::cout << to_print << std::flush;
    }

    Command read()
    {
        char data[BUFF_SIZE];
        boost::system::error_code error;
        size_t length = socket_.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof)   return Command{"eof",3};    // Connection closed cleanly by peer.
        else if (error)     throw boost::system::system_error(error);       // Some other error.

        {
            auto this_scope = lock();
            std::cout << "data received : "     <<  data
                      << "len = "               <<  length
                      << std::endl;
        }

        return Command{data,length};
    }

    void write(const std::string& response)
    {
        boost::asio::write(socket_, boost::asio::buffer(response));
    }

    bool prompt_and_check_password()
    {
        write("220 welcome to Hui Xie's FTP server\r\n");
        auto user = read().argument();
        write("331 password pls.\r\n");
        auto pwd = read().argument();

        return user_table_->check(user, pwd);
    }

    void do_session()
    {
        try
        {
            if(!prompt_and_check_password())        return;

            write("230 User logged in.\r\n");
            for(auto cmd = read();/*  */; cmd = read())
            {

                if(cmd == "QUIT")
                {
                    write("211 Bye.\r\n");          break;
                }

                if(cmd == "SYST")
                {
                    write("215 Ubuntu 14.04\r\n");  continue;
                }

                if(cmd == "PASV")
                {
                    write("227 Entering Passive Mode (127,0,0,1,22,46)\r\n");continue;
                }

                if(cmd == "LIST")
                {
                    write("150\r\n");continue;
                }

                write("502 Command not implemented.\r\n");
            }
        }
        catch (std::exception& e)
        {
            std::cerr << ">exception in thread: " << e.what() << "\n";
        }

        auto id = std::this_thread::get_id();
        std::cout << "\n>thread [" << id <<"] exit" << std::endl;
    }
};

}//end of namespace myftp
#endif // _SESSION_H
