#include "../../include/lesson5/Server.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/io_service.hpp"

Server::Server( io_service& ios, short port )
  : _ios( ios ), _acceptor( ios, ip::tcp::endpoint( ip::tcp::v4(), port ) )
{
  std::cout << "[Server]: Running on port " << port << std::endl;
  start_accept();
}

void Server::start_accept()
{
  Session* new_session = new Session( _ios );
  _acceptor.async_accept( new_session->Socket(),
                          std::bind( &Server::handle_accept, this, new_session, std::placeholders::_1 ) );
}

void Server::handle_accept( Session* new_session, const boost::system::error_code& error )
{
  if ( !error ) {
    new_session->Start();
  } else {
    delete new_session;
  }
  start_accept();
}