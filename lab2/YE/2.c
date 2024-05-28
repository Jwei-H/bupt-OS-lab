#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <cstring>


// 定义信号量操作结构体
struct sembuf acquire = {0, -1, SEM_UNDO};  // P操作
struct sembuf release = {0, 1, SEM_UNDO};   // V操作

int main() {
    // 创建共享内存
    key_t key = ftok("/tmp", 'A');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    char *shmaddr = (char*) shmat(shmid, (void*)0, 0);

    // 创建信号量集
    int semid = semget(key, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1); // 初始化信号量值为1，表示资源可用

    // 进程C
    if (fork() == 0) {
        std::cout << "Process C is running..." << std::endl;
        // 获取信号量
        semop(semid, &acquire, 1);
        // 写入共享内存
        std::strcpy(shmaddr, "Hello from Process C!");
        std::cout << "Process C wrote to shared memory" << std::endl;
        // 释放信号量
        semop(semid, &release, 1);
        return 0;
    }

    // 进程D
    if (fork() == 0) {
        std::cout << "Process D is running..." << std::endl;
        // 获取信号量
        semop(semid, &acquire, 1);
        // 读取共享内存
        std::cout << "Process D read from shared memory: " << shmaddr << std::endl;
        // 释放信号量
        semop(semid, &release, 1);
        return 0;
    }

    // 等待子进程结束
    for (int i = 0; i < 2; ++i) {
        wait(NULL);
    }

    // 删除共享内存和信号量
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

