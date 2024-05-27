#include <iostream>
#include <thread>
#include "sharedbuffer.cpp"
#include "producer.cpp"
#include "consumer.cpp"

int main() 
{
    // 创建共享缓冲区对象
    SharedBuffer buffer;

    // 创建生产者和消费者对象，传递共享缓冲区对象作为参数
    Producer producer(buffer);
    Consumer consumer(buffer);

    // 创建生产者线程和消费者线程
    std::thread producerThread(&Producer::produce, &producer);
    std::thread consumerThread(&Consumer::consume, &consumer);

    // 等待线程结束
    producerThread.join();
    consumerThread.join();

    return 0;
}
