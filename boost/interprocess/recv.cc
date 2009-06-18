#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace boost::interprocess;

int main()
{
    try {
        // Open a message queue.
        message_queue mq
            (open_only,
             "message_queue"
            );

        unsigned int priority;
        std::size_t recvd_size;

        char buff[200];
        mq.receive(buff, sizeof(buff), recvd_size, priority);
        std::cout << "recvd_size:   " << recvd_size << std::endl;
        std::string str(buff);
        std::cout << str << std::endl;
    } catch (interprocess_exception& ex) {
        message_queue::remove("message_queue");
        std::cout << ex.what() << std::endl;
        return 1;
    }

    message_queue::remove("message_queue");
    return 0;
}

