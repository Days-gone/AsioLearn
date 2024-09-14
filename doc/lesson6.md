# Using false Closure to Fix the potential bug
The old version has bug: when the client suddenly disconnect, causing the server class
object delete twice!(once from the handle_read error deal, once from the handle_write error deal) Which is very dangerous, this time we will using false closure to fix it, mainly using the shared_ptr to manage the object's life cycle.

We are using lambda function to extend the life-cycle of the object, and the lambda function will be called when the object is deleted. So the ref-count of the smart-ptr will increase.