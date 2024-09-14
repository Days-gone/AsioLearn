#pragma once
#include "./../include/lesson6/Session.hpp"
#include "boost/asio/io_service.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <map>
#include <memory>
using namespace boost::asio;

class Server
{
public:
  // io_service is a typedef of io_context, they are the same thing
  Server( io_service& ios, short port );
  void remove_session( const std::string& uuid );

private:
  void start_accept();
  // event driven
  void handle_accept( std::shared_ptr<Session> new_session, const boost::system::error_code& error );
  io_service& _ios;
  ip::tcp::acceptor _acceptor;
  std::map<std::string, std::shared_ptr<Session>> _sessions;
};