#include "../../include/lesson4/Session.hpp"
#include "boost/asio/registered_buffer.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

Session::Session( std::shared_ptr<ip::tcp::socket> socket )
{
  std::cout << "Session Constructed" << std::endl;
}

void Session::Connect( const ip::tcp::endpoint& ep )
{
  std::cout << "Session::Connect" << std::endl;
  _socket->connect( ep );
}

// Not actually used in practice
// void Session::WriteToSocketErrVersion( const std::string& buf )
// {
//   _send_node = std::make_shared<MsgNode>( buf.c_str(), buf.length() );
//   this->_socket->async_write_some(
//     buffer( _send_node->_msg, _send_node->_total_length ),
//     std::bind( &Session::WriteCallBackErrVersion, this, std::placeholders::_1, std::placeholders::_2, _send_node
//     ) );
// }

// Not actually used in practice
// Cause the user call the WriteToSocket many times may cause the order disrupt
/*
    WriteToSocketErr("Hello World!");
    //用户无感知下层调用情况又一次发送了数据
    WriteToSocketErr("Hello World!");
    May Get: HelloHello World! World!
*/
// void Session::WriteCallBackErrVersion( const boost::system::error_code& ec,
//                              std::size_t bytes_transferred,
//                              std::shared_ptr<MsgNode> msg)
// {
//   if (bytes_transferred + msg->_cur_length < msg->_total_length) {
//     _send_node->_cur_length += bytes_transferred;
//     this->_socket->async_write_some(
//       buffer( msg->_msg + msg->_cur_length, msg->_total_length - msg->_cur_length ),
//       std::bind( &Session::WriteCallBackErrVersion, this, std::placeholders::_1, std::placeholders::_2, msg ) );
//   }
// }

// Todo: finish the right version of the WriteToSocket & WriteCallBack.

void Session::WriteToSocket( const std::string& buf )
{
  _send_queue.emplace( new MsgNode( buf.c_str(), buf.length() ) );
  if ( _send_pending ) {
    return;
  }
  _socket->async_write_some(
    buffer( buf ), std::bind( &Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2 ) );
  _send_pending = true;
}

void Session::WriteCallBack( const boost::system::error_code& ec, std::size_t bytes_transferred )
{
  if ( ec ) {
    std::cout << "Error: " << ec.message() << std::endl;
    return;
  }
  if ( _send_queue.empty() ) {
    _send_pending = false;
    return;
  }
  // get the queue header
  auto& msg = _send_queue.front();
  // if not finish
  if ( msg->_cur_length < msg->_total_length ) {
    _socket->async_write_some(
      buffer( msg->_msg + msg->_cur_length, msg->_total_length - msg->_cur_length ),
      std::bind( &Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2 ) );
    return;
  }
  // if finish
  _send_queue.pop();
  if ( _send_queue.empty() ) {
    _send_pending = false;
    return;
  }

  // After pop, do we still have node to send?
  if ( !_send_queue.empty() ) {
    auto& msg = _send_queue.front();
    _socket->async_write_some(
      buffer( msg->_msg, msg->_total_length ),
      std::bind( &Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2 ) );
  }
}

void Session::AllWriteToSocket( const std::string& buf )
{
  _send_queue.emplace( new MsgNode( buf.c_str(), buf.length() ) );
  if ( _send_pending ) {
    return;
  }
  _socket->async_send(
    buffer( buf ), std::bind( &Session::AllWriteCallBack, this, std::placeholders::_1, std::placeholders::_2 ) );
  _send_pending = true;
}

void Session::AllWriteCallBack( const boost::system::error_code& ec, std::size_t bytes_transferred )
{
  if ( ec ) {
    std::cout << "Error: " << ec.message() << std::endl;
    return;
  }
  _send_queue.pop();
  if ( _send_queue.empty() ) {
    _send_pending = false;
  }
  if ( !_send_queue.empty() ) {
    auto& msg = _send_queue.front();
    _socket->async_send(
      buffer( msg->_msg, msg->_total_length ),
      std::bind( &Session::AllWriteCallBack, this, std::placeholders::_1, std::placeholders::_2 ) );
  }
}

void Session::AllReadFromSocket(const std::string& buf) {
  if (_recv_pending) {
    return ;
  }

  _recv_node =std::make_shared<MsgNode>(Session::RECV_SIZE);
  _socket->async_receive(buffer(_recv_node->_msg, _recv_node->_total_length), std::bind(&Session::AllReadCallBack,this, std::placeholders::_1, std::placeholders::_2));
  _recv_pending = true;
}

void Session::AllReadCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred) {
  if (ec) {
    std::cout << "Error: " << ec.message() << std::endl;
    return;
  }
  _recv_node->_cur_length += bytes_transferred;
  // throw the data received into the handler thread, omited here
  // callback from receive func, means that given length has been received
  // so setting the _recv_pending to false
  _recv_pending = false;
  _recv_node = nullptr;
}