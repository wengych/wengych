#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>

using namespace boost::interprocess;

int main()
{
    try {
        // Erase previous message queue
        message_queue::remove("message_queue");

        // Create a message_queue.
        message_queue mq
            (create_only,
             "message_queue",
             1000,
             sizeof(char) * 200
            );

        char msg[] = "hello.";
        std::cout << "msg size:  " << sizeof(msg) / sizeof(char) << std::endl;
        mq.send(msg, sizeof(msg) / sizeof(char), 0);

    } catch (interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "error" << std::endl;
        return 1;
    }

    return 0;
}

