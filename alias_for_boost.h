#ifndef _ALIAS_FOR_BOOST_H
#define _ALIAS_FOR_BOOST_H

#include <boost/asio.hpp>

namespace myftp {

  using Tcp         =   boost::asio::ip::tcp;
  using Acceptor    =   Tcp::acceptor;
  using Io_service  =   boost::asio::io_service;

  const unsigned BUFF_SIZE = 512;
};

#endif
