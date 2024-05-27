#ifndef SHAREDBUFFER_H
#define SHAREDBUFFER_H

#include <mutex>
#include <condition_variable>
#include <iostream>

const int BUFFER_SIZE = 10; // 缓冲区大小

class SharedBuffer 
{
public:
    SharedBuffer() : itemCount(0) {}

    void produce(int item);
    void consume();

private:
    int buffer[BUFFER_SIZE]; // 共享缓冲区
    int itemCount; // 缓冲区中当前物品数量
    std::mutex mtx;
    std::condition_variable cv;
};

// sharedbuffer.cpp的代码

void SharedBuffer::produce(int item) 
{
    std::unique_lock<std::mutex> lock(mtx);

    // 如果缓冲区已满，则等待
    cv.wait(lock, [this] { return itemCount < BUFFER_SIZE; });

    // 生产物品
    buffer[itemCount++] = item;
    std::cout << "Produced: " << item << std::endl;

    // 通知消费者可以消费了
    cv.notify_all();
}

void SharedBuffer::consume() 
{
    std::unique_lock<std::mutex> lock(mtx);

    // 如果缓冲区为空，则等待
    cv.wait(lock, [this] { return itemCount > 0; });

    // 消费物品
    int item = buffer[--itemCount];
    std::cout << "Consumed: " << item << std::endl;

    // 通知生产者可以生产了
    cv.notify_all();
}

#endif // SHAREDBUFFER_H
