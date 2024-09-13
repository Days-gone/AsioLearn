#include <cstring>
class MsgNode
{
public:
  // constructor for Write MsgNode
  MsgNode( const char* msg, int total_length )
  {
    _msg = new char[total_length];
    memcpy( _msg, msg, total_length );
  }
  // constructor for Read MsgNode
  MsgNode( int total_length ) { _msg = new char[total_length]; }
  ~MsgNode() { delete[] _msg; }
  // data head address
  char* _msg;
  // data total length
  int _total_length;
  // curent length
  int _cur_length;
};