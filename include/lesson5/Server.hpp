#include "Session.hpp"
#include "boost/asio/io_service.hpp"
#include <boost/asio.hpp>
using namespace boost::asio;

class Server
{
public:
  // io_service is a typedef of io_context, they are the same thing
  Server( io_service& ios, short port );

private:
  void start_accept();
  // event driven
  void handle_accept( Session* new_session, const boost::system::error_code& error );
  io_service& _ios;
  ip::tcp::acceptor _acceptor;
};