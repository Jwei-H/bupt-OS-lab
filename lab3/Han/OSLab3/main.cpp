#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include "ringQueue.h"
#include "task.h"

void *ProductorRoutine(void *product) {
    RingQueue<Task> *rqueue = static_cast<RingQueue<Task> *>(product);
    const std::string oper = "+-*/";
    while (1) {
        //模拟构建一个任务
        int x = rand() % 1000;
        int y = rand() % 2000;
        char op = oper[rand() % oper.size()];
        Task t(x, y, op, myMath);//构建任务对象
        rqueue->Push(t);
        std::cout << pthread_self() << "生产者提交任务： " << t.toString() << std::endl;
        sleep(1);
    }
}

void *ConsumerRoutine(void *consume) {
    RingQueue<Task> *rqueue = static_cast<RingQueue<Task> *>(consume);
    while (1) {
        Task t;
        rqueue->Pop(&t);
        std::cout <<pthread_self() << "消费者完成任务: " << t() << std::endl;
    }
}

int main() {
    RingQueue<Task> *rq = new RingQueue<Task>();
    pthread_t p[3], c[2];//定义生产者消费者线程
    for (int i = 0; i < 3; ++i)
        pthread_create(p + i, nullptr, ProductorRoutine, rq);
    for (int i = 0; i < 2; ++i)
        pthread_create(c + i, nullptr, ConsumerRoutine, rq);
    for (int i = 0; i < 3; ++i)
        pthread_join(p[i], nullptr);
    for (int i = 0; i < 2; ++i)
        pthread_join(c[i], nullptr);
    return 0;
}