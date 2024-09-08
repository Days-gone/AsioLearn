# Endpoint
in boost.asio we have a class called `ip::tcp::endpoint` which is used to represent a connection endpoint. It is a combination of an IP address and a port number. It is used to specify the remote endpoint to which a socket will connect or bind to. The `ip::tcp::endpoint` class is defined in the `boost::asio::ip` namespace.
we will introduce the followings  
- [ ] Create a endpoint

# Socket
A socket is an endpoint for communication between two machines. It is used to send and receive data. In boost.asio, we have a class called `ip::tcp::socket` which is used to represent a TCP socket. The `ip::tcp::socket` class is defined in the `boost::asio::ip` namespace.And we will introduce the special socket called `acceptor` which is used to accept incoming connections.
- [ ] Create a Socket
- [ ] Create a Acceptor
- [ ] Bind a Acceptor/Socket to an endpoint
- [ ] Listen for incoming connections
#

# Extra
the buffer model of the asio is `asio::mutable_buffer` and `asio::const_buffer` which is used to represent a buffer of data. The `asio::mutable_buffer` class is used to represent a buffer of mutable data, while the `asio::const_buffer` class is used to represent a buffer of constant data. The `asio::mutable_buffer` and `asio::const_buffer` classes are defined in the `boost::asio` namespace.

# Thanks
thanks for the tutorial material of from the
[Blog of llfc](https://llfc.club)