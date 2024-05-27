#ifndef CONSUMER_H
#define CONSUMER_H

#include "sharedbuffer.cpp"

class Consumer 
{
public:
    Consumer() = default; // 默认构造函数

    Consumer(SharedBuffer& buffer) : buffer(buffer) {}

    void consume();

private:
    SharedBuffer& buffer;
};


// consumer.cpp的代码
#include <iostream>

void Consumer::consume() 
{
    for (int i = 1; i <= 5; ++i) { // 消费5个物品
        buffer.consume();
    }
}

#endif // CONSUMER_H
