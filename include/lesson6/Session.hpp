#pragma once
#include "boost/asio/io_service.hpp"
#include "boost/uuid/uuid.hpp"
#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
using namespace boost::asio;
class Server;
class Session : public std::enable_shared_from_this<Session>
{
public:
  Session( io_service& ios, Server* server ) : _socket( ios ), _server( server )
  {
    boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
    _uuid = boost::uuids::to_string( a_uuid );
  }
  ip::tcp::socket& Socket() { return _socket; }
  void Start();
  // get uuid
  const std::string& get_uuid() { return _uuid; }

private:
  // read call back
  void handle_read( const boost::system::error_code& error,
                    size_t bytes_transfered,
                    std::shared_ptr<Session> self );
  // write call back
  void handle_write( const boost::system::error_code& error, std::shared_ptr<Session> self );

private:
  std::string _uuid;
  ip::tcp::socket _socket;
  Server* _server;
  enum
  {
    max_length = 1024
  };
  char _data[max_length];
};