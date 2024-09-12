
#include "boost/asio/io_service.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/read.hpp"
#include "boost/asio/read_until.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/system/system_error.hpp"
#include <cstddef>
#include <iostream>
#include <string>

using namespace boost::asio;

// sync write api
void Write_some_toSocket( ip::tcp::socket& sock )
{
  std::string data = "hello, world!\n";
  std::size_t bytes_writen = 0;

  // loop sending
  while ( bytes_writen != data.length() ) {
    // write some needs
    // 1.the address of the start byte
    // 2.the bytes you wanna write
    bytes_writen += sock.write_some( buffer( data.c_str() + bytes_writen, data.length() - bytes_writen ) );
  }
}

// sync write api
void Send_toSocket( ip::tcp::socket& sock )
{
  // get a ip address first
  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io service
    io_service ios;
    // get a socket
    ip::tcp::socket sock( ios, endpoint.protocol() );
    // connect the socket
    sock.connect( endpoint );
    // send data
    std::string data = "hello, world!\n";
    int bytes_sent = sock.send( buffer( data.c_str(), data.length() ) );
    if ( bytes_sent <= 0 ) {
      std::cerr << "send failed" << std::endl;
      return;
    }
  } catch ( boost::system::system_error& e ) {
    std::cerr << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
  }
}

// sync read api
std::string read_some_fromSocket( ip::tcp::socket& sock )
{
  constexpr unsigned char MESSAGE_SIZE = 7;
  char buf[MESSAGE_SIZE];
  std::size_t bytes_read = 0;

  // loop read_some
  while ( bytes_read != MESSAGE_SIZE ) {
    bytes_read += sock.read_some( buffer( buf + bytes_read, MESSAGE_SIZE - bytes_read ) );
  }

  return std::string( buf, bytes_read );
}

// calling example
void Call_read_some_fromSocket()
{
  // get the peer endpoint
  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io service
    io_service ios;
    // get a socket
    ip::tcp::socket sock( ios, endpoint.protocol() );
    // connect the socket
    sock.connect( endpoint );
    // read from socket
    read_some_fromSocket( sock );
  } catch ( boost::system::system_error& e ) {
    std::cerr << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
    return;
  }
}

// sync read api
void receive_fromSocket( ip::tcp::socket& sock )
{
  // get a ip address
  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io service
    io_service ios;
    // get a socket
    ip::tcp::socket sock( ios, endpoint.protocol() );
    // connect the socket
    sock.connect( endpoint );
    // read from socket
    constexpr unsigned char BUF_SIZE = 7;
    char rec_buffer[BUF_SIZE];
    int receive_length = sock.receive( buffer( rec_buffer, BUF_SIZE ) );
    if ( receive_length <= 0 ) {
      std::cerr << "receive failed" << std::endl;
      return;
    }
  } catch ( boost::system::system_error& e ) {
    std::cerr << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
    return;
  }
}

// sync read api
void read_fromSocket( ip::tcp::socket& sock )
{
  // get a ip address
  std::string ip_address = "127.0.0.1";
  unsigned short port = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( ip_address ), port );
    // get a io service
    io_service ios;
    // get a socket
    ip::tcp::socket sock( ios, endpoint.protocol() );
    // connect the socket
    sock.connect( endpoint );
    // read from socket
    constexpr unsigned char BUF_SIZE = 7;
    char rec_buffer[BUF_SIZE];
    int receive_length = boost::asio::read( sock, buffer( rec_buffer, BUF_SIZE ) );
    if ( receive_length <= 0 ) {
      std::cerr << "receive failed" << std::endl;
      return;
    }
  } catch ( boost::system::system_error& e ) {
    std::cerr << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
    return;
  }
}

// read until encounter some specific character
std::string read_until_fromSocket( ip::tcp::socket& sock )
{
  // get a ip address
  streambuf buf;
  read_until( sock, buf, '\n' );
  std::string message;

  std::istream input_stream( &buf );
  std::getline( input_stream, message );
  return message;
}