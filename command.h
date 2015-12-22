#ifndef _COMMAND_H
#define _COMMAND_H

#include <iostream>
#include <string>
#include <cassert>

namespace myftp {


  /**
   * ftp commands 
   */

class Command {
public:

  Command() = delete;

  Command(const char* msg, std::size_t len):
    _cmd{}, _args{}
  {
    len -= 2; // 命令以\r\n结尾

    unsigned idx = 0;
    for ( ; idx != len && !std::isspace(msg[idx]); ++idx)
      _cmd.push_back(msg[idx]);
    
    if (idx < len) 
      for (++idx; idx != len; ++idx) _args.push_back(msg[idx]);
  }

  const std::string& cmd() const
  {
    return _cmd;
  }

  const std::string& argument() const
  {
    return _args;
  } 

private:
    std::string _cmd;
    std::string _args;
};

inline bool operator !=(const Command& lhs, const std::string& rhs)
{
  return lhs.cmd() != rhs;
}

inline bool operator !=(const std::string& lhs, const Command& rhs)
{
  return lhs != rhs.cmd();
}

inline bool operator ==(const Command& lhs, const std::string& rhs)
{
  return lhs.cmd() == rhs;
}

inline bool operator ==(const std::string& lhs, const Command& rhs)
{
  return lhs == rhs.cmd();
}

inline std::ostream&
operator << (std::ostream& os, const Command& cmd)
{
  os << "[" << cmd.cmd() << "]"
    << "[" << cmd.argument() << "]";
  return os;
}


} // end of myftp namespace 

#endif /* _COMMAND_H */

