#include "../../include/lesson6/Server.hpp"
#include "boost/asio/io_service.hpp"
#include <boost/asio.hpp>

int main() {
    io_service ios;
    unsigned short port = 3333;
    Server server(ios, port);
    // call the run func to start the event loop
    ios.run();
    return 0;
}