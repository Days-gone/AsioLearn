#include "MsgNode.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/system/detail/error_code.hpp"
#include <boost/asio.hpp>
#include <cstddef>
#include <memory>
#include <queue>
using namespace boost::asio;
class Session
{
public:
  Session( std::shared_ptr<ip::tcp::socket> socket );
  void Connect( const ip::tcp::endpoint& ep );
  // ErrVersion for the wrong version which may cause the order disrupt
  // passing the MsgNode as parameters to extend the life-cycle of MsgNode
  // void WriteCallBackErrVersion( const boost::system::error_code& ec,
  //                               std::size_t bytes_transferred,
  //                               std::shared_ptr<MsgNode> );
  // void WriteToSocketErrVersion( const std::string& buf );
  
  // the following version is right!
  // Wrap the async_write_some with a queue to ensure the order
  void WriteCallBack( const boost::system::error_code& ec, std::size_t bytes_transferred );
  void WriteToSocket( const std::string& buf );

  // Wrap the async_send which will send all the data then trigger the callback func
  void AllWriteToSocket(const std::string& buf);
  void AllWriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);

  // Wrap the async_receive which receve all the data then trigger
  void AllReadFromSocket(const std::string& buf);
  void AllReadCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);

private:
  static constexpr int RECV_SIZE = 1024; 
  std::shared_ptr<ip::tcp::socket> _socket;
  std::queue<std::shared_ptr<MsgNode>> _send_queue;
  std::shared_ptr<MsgNode> _recv_node;
  bool _send_pending;
  bool _recv_pending;

};