#include <boost/asio.hpp>
#include <iostream>
using namespace boost::asio;

class Session
{
public:
  Session( boost::asio::io_context& ioc ) : _socket( ioc ) {}
  ip::tcp::socket& Socket() { return _socket; }
  void Start();

private:
  // read call back
  void handle_read( const boost::system::error_code& error, size_t bytes_transfered );
  // write call back
  void handle_write( const boost::system::error_code& error );

private:
  ip::tcp::socket _socket;
  enum
  {
    max_length = 1024
  };
  char _data[max_length];
};