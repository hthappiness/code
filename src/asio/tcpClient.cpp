
//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;
#if 0
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
#endif
    boost::system::error_code error = boost::asio::error::host_not_found;
    boost::asio::ip::address add;
    add.from_string("127.0.0.1");

    tcp::socket socket(io_context);
    tcp::endpoint endpoint(add, short(13));
    socket.connect(endpoint, error);

#if 0
    tcp::resolver resolver(io_context);
    tcp::resolver::query query("localhost", "13");

    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    boost::system::error_code error = boost::asio::error::host_not_found;
    boost::asio::ip::tcp::endpoint endpoint;
    while (error && endpoint_iterator != end)
    {
        endpoint = *endpoint_iterator ;
        socket.close();
        socket.connect(endpoint, error);
        endpoint_iterator++ ;
    }

#endif

#if 1
    boost::asio::io_context my_io_ctx ;
    boost::asio::ip::tcp::resolver resolver(my_io_ctx);
    boost::asio::ip::tcp::resolver::query query("www.baidu.com", "http");
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end; // End marker.
    
    while (iter != end)
    {
      boost::asio::ip::tcp::endpoint endpoint = *iter++;
      std::cout << endpoint << std::endl;
    }
#endif
    for (;;)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}