#ifndef OSLAB2_SHAREDMOMERY_H
#define OSLAB2_SHAREDMOMERY_H
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>





#endif //OSLAB2_SHAREDMOMERY_H

using namespace std;

//使用信号量实现进程同步

// 初始化信号量
extern int init_semaphore();

// P操作，获取信号量
extern void P(int sem_id);

// V操作，释放信号量
extern void V(int sem_id);

//创建共享内存
extern int create_shm(int size);

//连接共享内存
extern int *connect_shm(int shm_id);

// 销毁共享内存和信号量
extern void destroy_shm(int shm_id, int *shm_ptr,int sem_id);