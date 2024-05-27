#ifndef PRODUCER_H
#define PRODUCER_H

#include "sharedbuffer.cpp"

class Producer 
{
public:
    // 默认构造函数
    //Producer() : buffer(new SharedBuffer()) {}

    // 带参数的构造函数
    Producer(SharedBuffer& buffer) : buffer(buffer) {}

    void produce();

private:
    SharedBuffer& buffer;
};

// producer.cpp的代码
#include <iostream>

void Producer::produce() 
{
    for (int i = 1; i <= 5; ++i) { // 生产5个物品
        buffer.produce(i);
    }
}

#endif // PRODUCER_H
