#include "boost/asio/error.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/detail/error_code.hpp"
#include <boost/asio.hpp>
#include <cstring>
#include <exception>
#include <iostream>
#include <unistd.h>

using namespace boost::asio;
constexpr int MAX_SIZE = 1024;

int main()
{

  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;
  std::cout << "[Client]: Connecting to " << ip_address << " on port " << port << std::endl;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io_service
    boost::asio::io_service ios;
    // get a socket
    ip::tcp::socket socket( ios );
    boost::system::error_code ec = error::host_not_found;
    auto _ = socket.connect( endpoint, ec );
    if ( ec ) {
      throw std::runtime_error( ec.message() );
    }

    char request[MAX_SIZE];
    std::cin.getline( request, MAX_SIZE );
    size_t rq_length = strlen( request );
    write( socket, buffer( request, rq_length ) );

    char reply[MAX_SIZE];
    size_t rp_length = read( socket, buffer( reply, rq_length ) );
    std::cout << "[Client]: Reply From Server: ";
    std::cout.write( reply, rp_length );
    std::cout << "\n";
  } catch ( std::exception& e ) {
    std::cerr << e.what() << std::endl;
    return 0;
  }
}