#include "../../include/lesson5/Session.hpp"
#include "boost/asio/registered_buffer.hpp"
#include "boost/asio/write.hpp"
#include "boost/system/detail/error_code.hpp"
#include <cstring>

void Session::Start()
{
  // new thread do the things bellow:
  memset( _data, 0, Session::max_length );
  _socket.async_read_some( buffer( _data, Session::max_length ),
                           std::bind( &Session::handle_read, this, std::placeholders::_1, std::placeholders::_2 ) );
}

void Session::handle_read( const boost::system::error_code& error, size_t bytes_transfered )
{
  if ( !error ) {
    std::cout << "[Server]: Receive: " << _data << "\n";
    async_write( _socket,
                 buffer( _data, bytes_transfered ),
                 std::bind( &Session::handle_write, this, std::placeholders::_1 ) );
  } else {
    delete this;
  }
}

void Session::handle_write( const boost::system::error_code& e )
{
  if ( !e ) {
    memset( _data, 0, max_length );
    _socket.async_read_some(
      buffer( _data, Session::max_length ),
      std::bind( &Session::handle_read, this, std::placeholders::_1, std::placeholders::_2 ) );
  } else {
    delete this;
  }
}
