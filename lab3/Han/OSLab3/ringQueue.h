//
// Created by han on 4/15/24.
//

#ifndef OSLAB3_RINGQUEUE_H

#include <iostream>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <pthread.h>

#define OSLAB3_RINGQUEUE_H


static const int gcap = 5;

template<class T>
class RingQueue {
private:
    void P(sem_t &spaceSem) {
        sem_wait(&spaceSem);
    }

    void V(sem_t &dataSem) {
        sem_post(&dataSem);
    }

public:
    RingQueue(const int &cap = gcap)
            : _queue(cap), _cap(cap), _productorStep(0), _consumerStep(0) {
        sem_init(&_spaceSem, 0, _cap);
        sem_init(&_dataSem, 0, 0);
        pthread_mutex_init(&_pmutex, nullptr);
        pthread_mutex_init(&_cmutex, nullptr);
    }

    void Push(const T &in)//向环形队列中push数据
    {
        P(_spaceSem);

        pthread_mutex_lock(&_pmutex);
        _queue[_productorStep++] = in;
        _productorStep %= _cap;

        pthread_mutex_unlock(&_pmutex);
        V(_dataSem);
    }

    void Pop(T *out)//向环形队列中pop数据,out是输出型参数
    {
        P(_dataSem);

        pthread_mutex_lock(&_cmutex);
        *out = _queue[_consumerStep++];
        _consumerStep %= _cap;

        pthread_mutex_unlock(&_cmutex);
        V(_spaceSem);
    }

    ~RingQueue() {
        sem_destroy(&_spaceSem);
        sem_destroy(&_dataSem);
        pthread_mutex_destroy(&_pmutex);
        pthread_mutex_destroy(&_cmutex);
    }

private:
    std::vector<T> _queue;//vector模拟队列
    int _cap;//队列的最大容量
    sem_t _spaceSem;//生产者信号量，表明环形队列中剩余空间资源数量
    sem_t _dataSem;//消费者信号量，表明环形队列中存在的数据资源数量
    int _productorStep;//生产者在循环列表的脚步
    int _consumerStep;//消费者在循环列表的脚步
    pthread_mutex_t _pmutex;//生产者锁
    pthread_mutex_t _cmutex;//消费者锁
};

#endif //OSLAB3_RINGQUEUE_H
