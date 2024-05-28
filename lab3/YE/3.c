#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        sleep(rand() % 3);  // 模拟生产时间
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // 生产物品
        buffer[item] = rand() % 100;
        printf("生产: %d\n", buffer[item]);
        item = (item + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item = 0;
    while (1) {
        sleep(rand() % 3);  // 模拟消费时间
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // 消费物品
        printf("消费: %d\n", buffer[item]);
        buffer[item] = -1; // 重置缓冲区
        item = (item + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 初始化信号量和互斥锁
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 清理资源
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
