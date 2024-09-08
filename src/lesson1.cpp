#include "boost/asio/ip/address.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/detail/error_code.hpp"
#include <boost/asio.hpp>
#include <iostream>

void client_endpoint()
{
  using namespace boost::asio;
  // i am client, i want to connect to server
  // server address
  std::string address = "127.0.0.1";
  unsigned short port = 3333;

  // create a error code to check if the ip address is valid
  boost::system::error_code ec;

  // get a ip_address object
  ip::address ip_address = ip::address::from_string( address, ec );
  if ( ec.value() != 0 ) {
    std::cerr << "Invalid address: " << address << std::endl;
    return;
  }

  // create a endpoint object
  ip::tcp::endpoint endpoint( ip_address, port );
}

void server_endpoint()
{
  using namespace boost::asio;
  // i am server, i want to listen on port 3333
  // listen port
  unsigned short port = 3333;

  // server could get ip_address from any() interface
  ip::address ip_address = ip::address_v4::any();

  // create a endpoint object
  ip::tcp::endpoint endpoint( ip_address, port );
}

void create_normal_socket()
{
  using namespace boost::asio;

  // create a io_context object
  io_context io_service;

  // create a protocol
  ip::tcp protocol = ip::tcp::v4();

  // create a socket object
  ip::tcp::socket socket( io_service, protocol );

  // using a boost::error_code object to check if the socket is created successfully
  boost::system::error_code ec;
  // Add _ to remove warning
  auto _ = socket.open( protocol, ec );
  if ( ec.value() != 0 ) {
    std::cerr << "Failed to open socket: " << ec.message() << std::endl;
    return;
  }
}

void create_acceptor()
{
  using namespace boost::asio;

  // create a io_context object
  io_context io_service;

  // create a protocol
  ip::tcp protocol = ip::tcp::v4();

  // create a acceptor object
  ip::tcp::acceptor acceptor( io_service );

  // boost::error_code object to check if the acceptor is created successfully
  boost::system::error_code ec;
  if ( acceptor.open( protocol, ec ).value() != 0 ) {
    std::cerr << "Failed to open acceptor: " << ec.message() << std::endl;
    return;
  }

  // Add _ to remove warning
  auto _ = acceptor.open( protocol, ec );
  if ( ec.value() != 0 ) {
    std::cerr << "Failed to open acceptor: " << ec.message() << std::endl;
    return;
  }
}

void bind_acceptor()
{
  // 1. create a address, protocol, socket.
  using namespace boost::asio;
  unsigned short port = 3333;
  ip::tcp::endpoint endpoint( ip::address_v4::any(), port );

  io_context io_service;
  ip::tcp::acceptor acceptor( io_service, endpoint.protocol() );

  // get a boost::error_code object to check if the bind is successful
  boost::system::error_code ec;

  // 2. bind the socket to the endpoint
  auto _ = acceptor.bind( endpoint, ec );

  if ( ec.value() != 0 ) {
    std::cerr << "Failed to bind acceptor: " << ec.message() << std::endl;
    return;
  }
}

void connect_endpoint()
{
  // i am client, i wanna connect to server
  using namespace boost::asio;

  // 1. get a endpoint, protocol, socket
  std::string address = "127.0.0.1";
  unsigned short number = 3333;

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address::from_string( address ), number );
    // get a io_context for socket
    io_context io_service;
    // get a socket
    ip::tcp::socket socket( io_service, endpoint.protocol() );

    // 2. connect to the server
    boost::system::error_code ec;
    auto _ = socket.connect( endpoint, ec );

    if ( ec.value() != 0 ) {
      std::cerr << "Failed to connect to server: " << ec.message() << std::endl;
      return;
    }
  } catch ( boost::system::error_code& e ) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}

void server_accept()
{

  using namespace boost::asio;

  constexpr int PENDING_QUEUE_MAX_SIZE = 10;

  unsigned short port = 3333;

  // get a endpoint,

  try {
    // get a endpoint
    ip::tcp::endpoint endpoint( ip::address_v4::any(), port );
    // get a io_context for socket
    io_context io_service;
    // get a acceptor
    ip::tcp::acceptor acceptor( io_service, endpoint.protocol() );
    // bind the acceptor to the endpoint
    acceptor.bind( endpoint );
    // Start listening
    acceptor.listen( PENDING_QUEUE_MAX_SIZE );
    // get a new socket
    ip::tcp::socket socket( io_service );
    // accept the connection
    acceptor.accept( socket );
    // now the socket is connected to the client
  } catch ( boost::system::error_code& e ) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}