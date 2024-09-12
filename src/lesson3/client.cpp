#include "boost/asio/error.hpp"
#include "boost/asio/registered_buffer.hpp"
#include "boost/system/detail/error_code.hpp"
#include <boost/asio.hpp>
#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>

using namespace boost::asio;
constexpr int MAX_SIZE = 1024;

int main()
{
  // the server address
  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io service
    io_service service;
    // get a socket
    ip::tcp::socket socket( service );
    boost::system::error_code ec = boost::asio::error::host_not_found;
    // connect to the server
    auto _ = socket.connect( endpoint, ec );
    if ( ec ) {
      std::cerr << "Error: " << ec.message() << std::endl;
      return -1;
    }
    std::cout << "Enter Message:\n";

    // send the message to the server
    char request[MAX_SIZE];
    std::cin.getline( request, MAX_SIZE );
    std::size_t request_length = strlen( request );
    write( socket, buffer( request, request_length ) );

    // this is a echo server so the client should receive the same message length as has sent
    char rec_message[MAX_SIZE];
    std::size_t receive_length = read( socket, buffer( rec_message, request_length ) );
    std::cout << "Reply is : ";
    std::cout.write( rec_message, request_length );
    std::cout << "\n";
  } catch ( std::exception& e ) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return -1;
  }
}