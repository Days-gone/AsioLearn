# Async APIs
## Why use std::bind in the WriteToSocket?
`std::bind` is a standard library function used to create a new function object that binds a function or member function with a set of arguments. This allows for the delayed invocation of the function until it is needed. In the context of your code, the purpose of `std::bind` is as follows:

```cpp
std::bind( &Session::WriteCallBack, this, std::placeholders::_1, std::placeholders::_2, _send_node )
```

This `std::bind` call creates a new function object that binds to the `Session::WriteCallBack` member function and binds the following arguments to that function:

1. `&Session::WriteCallBack`: The member function to bind.
2. `this`: A pointer to the current `Session` object, as `WriteCallBack` is a member function that requires an object instance to invoke it.
3. `std::placeholders::_1` and `std::placeholders::_2`: Placeholders used to represent the first two arguments (i.e., `boost::system::error_code` and `std::size_t`) passed to the `async_write_some` call.
4. `_send_node`: Bound to the third parameter of `WriteCallBack`.

Therefore, the function object created by `std::bind` is equivalent to a function with the following signature:

```cpp
void WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred)
```

When the asynchronous write operation of `async_write_some` is completed, it invokes this function object and passes the `boost::system::error_code` and `std::size_t` parameters. Then, this function object calls the `Session::WriteCallBack` member function and passes `this`, `ec`, `bytes_transferred`, and `_send_node` as arguments to it.

In summary, `std::bind` is used to bind the `Session::WriteCallBack` member function with the current object instance and some arguments, so that it can be invoked when the asynchronous operation is completed.

# Sending Queue
Add sending queue to make it right for Session api.
Change the wrong version to the right version.
Wrap the async_write_some function will cause the recursive calling of the callback func
, we recommend using async_send func as a substitute.

# Async Read
same as the async_write_some and the async_send, Read also has async_read_some and async_receive, you can use them to implement the async read. Don't use async_xxxx_some 
and async_xxxxxx at the same time. We are gona wrap the async_receive directly.