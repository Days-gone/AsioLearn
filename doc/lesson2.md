# Sync Write
Introduce some apis of the boost.asio.

| write_some  
send the fixed length of data to the socket. If the write buffer is full, then write as much as possilbe and return value is bytes number written.

| send  
this function will automatically send all the data in the buffer. If the buffer is full, then the function will block until the buffer is not full. The return value is the bytes number written.

| write  
this function offer the facility of the scatter-gather I/O. Generally speaking we will send all the data or none of them. The return value is the bytes number written. If the tcp-write buffer is full, then the function will block until it could finish the send operation.

# Sync Read
Introduce some apis of the boost.asio.

| read_some
read fixed length bytes. If the read buffer is empty, then read as much as possible and return the bytes number read.

| receive
this function will automatically read all the data in the buffer. If the buffer is empty, then the function will block until the buffer is not empty. The return value is the bytes number read.

| read
this function offer the facility of the scatter-gather I/O. Generally speaking we will read all the data or none of them. The return value is the bytes number read. If the tcp-read buffer is empty, then the function will block until it could finish the read operation.