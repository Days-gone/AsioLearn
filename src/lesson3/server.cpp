#include "boost/asio/buffer.hpp"
#include "boost/asio/error.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/asio/ip/address_v4.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/detail/error_code.hpp"
#include "boost/system/system_error.hpp"
#include <boost/asio.hpp>
#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <set>
#include <thread>
#include <unistd.h>

using namespace boost::asio;
using SocketPtr = std::shared_ptr<ip::tcp::socket>;
constexpr int MAX_SIZE = 1024;

std::set<std::shared_ptr<std::thread>> thread_set;

void session( SocketPtr socket )
{
  try {
    for ( ;; ) {
      char data[MAX_SIZE];
      memset( data, 0, MAX_SIZE );
      boost::system::error_code ec;
      std::size_t length = socket->read_some( buffer( data, MAX_SIZE ), ec );
      if ( ec == error::eof ) {
        std::cout << "Connection closed by peer" << std::endl;
        break;
      } else if ( ec ) {
        throw boost::system::system_error( ec );
      }
      std::cout << "[Server]: PeerIP: " << socket->remote_endpoint().address().to_string() << "\n";
      std::cout << "[Server]: Received: " << data << "\n";

      write( *socket, buffer( data, length ) );
    }

  } catch ( std::exception& e ) {}
}

void server( io_service& ios, unsigned short port = 3333 )
{
  // get a endpoint first
  ip::tcp::endpoint endpoint( ip::address_v4::any(), port );
  // get a socket
  ip::tcp::acceptor acceptor( ios, endpoint );
  for ( ;; ) {
    SocketPtr socket( new ip::tcp::socket( ios ) );
    acceptor.accept( *socket );
    auto t = std::make_shared<std::thread>( session, socket );
    thread_set.insert( t );
  }
}

int main()
{
  // maintain the io_service and port number at main function
  unsigned short port = 3333;

  try {
    io_service ios;
    server( ios, port );
    for ( auto t : thread_set ) {
      // wait for all threads to finish
      t->join();
    }

  } catch ( std::exception& e ) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}