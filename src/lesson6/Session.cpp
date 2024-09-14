#include "../../include/lesson6/Session.hpp"
#include "../../include/lesson6/Server.hpp"
#include "boost/asio/write.hpp"
#include "boost/system/detail/error_code.hpp"
#include <cstring>
#include <memory>

void Session::Start()
{
  // new thread do the things bellow:
  memset( _data, 0, Session::max_length );
  _socket.async_read_some(
    buffer( _data, Session::max_length ),
    std::bind(
      &Session::handle_read, this, std::placeholders::_1, std::placeholders::_2, this->shared_from_this() ) );
}

void Session::handle_read( const boost::system::error_code& error,
                           size_t bytes_transfered,
                           std::shared_ptr<Session> self )
{
  if ( !error ) {
    std::cout << "[Server]: Receive: " << _data << "\n";
    async_write( _socket,
                 buffer( _data, bytes_transfered ),
                 std::bind( &Session::handle_write, this, std::placeholders::_1, self ) );
  } else {
    // delete this;
    // have used shared_from_this, so no need to delete this
    _server->remove_session( _uuid );
  }
}

void Session::handle_write( const boost::system::error_code& e, std::shared_ptr<Session> self )
{
  if ( !e ) {
    memset( _data, 0, max_length );
    _socket.async_read_some(
      buffer( _data, Session::max_length ),
      std::bind( &Session::handle_read, this, std::placeholders::_1, std::placeholders::_2, self ) );
  } else {
    _server->remove_session( _uuid );
  }
}
