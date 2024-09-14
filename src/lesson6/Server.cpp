#include "../../include/lesson6/Server.hpp"
#include "boost/asio/io_service.hpp"

Server::Server( io_service& ios, short port )
  : _ios( ios ), _acceptor( ios, ip::tcp::endpoint( ip::tcp::v4(), port ) )
{
  std::cout << "[Server]: Running on port " << port << std::endl;
  start_accept();
}

void Server::start_accept()
{
  auto new_session = std::make_shared<Session>( _ios, this );
  // Session* new_session = new Session( _ios );
  // new_session life-cycle is same as the bind-generated function, and its
  // ref-count increase by one here.
  // as long as the asio has not delete the bind-generated function, ths new_session
  // will be still alive.
  _acceptor.async_accept( new_session->Socket(),
                          std::bind( &Server::handle_accept, this, new_session, std::placeholders::_1 ) );
}

void Server::handle_accept( std::shared_ptr<Session> new_session, const boost::system::error_code& error )
{
  if ( !error ) {
    new_session->Start();
    _sessions[new_session->get_uuid()] = new_session;
  } else {
    // something goes wrong, no insert to the map
  }
  start_accept();
}

void Server::remove_session( const std::string& uuid )
{
  _sessions.erase( uuid );
}