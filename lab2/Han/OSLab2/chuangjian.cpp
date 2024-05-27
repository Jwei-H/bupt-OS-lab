#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define SHM_SIZE 512
#define SHM_KEY 1234
#define SEM_KEY 5678

// 定义信号量操作的结构体
struct sembuf acquire = {0, -1, SEM_UNDO};
struct sembuf release = {0, 1, SEM_UNDO};

// 定义共享内存中的复杂数据结构
struct ComplexData 
{
    char value[SHM_SIZE];
    // 这里可以根据需要定义更复杂的数据结构
};

int main() 
{
    int shmid;
    int semid;
    void *shmaddr;
    struct ComplexData *data;

    // 创建共享内存
    shmid = shmget(SHM_KEY, sizeof(struct ComplexData), IPC_CREAT | 0666);
    if (shmid == -1) 
    {
        perror("shmget");
        exit(1);
    }

    // 创建信号量
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) 
    {
        perror("semget");
        exit(1);
    }

    // 初始化信号量
    semctl(semid, 0, SETVAL, 1);

    // 将共享内存附加到进程地址空间
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *)-1) 
    {
        perror("shmat");
        exit(1);
    }

    // 使用信号量保护共享内存的访问
    semop(semid, &acquire, 1);

    // 将共享内存转换为复杂数据结构
    data = (struct ComplexData *)shmaddr;

    printf("输入写入共享内存的内容：");
    std::cin >> data->value; // 使用 std::cin 来读取用户输入

    // 释放信号量
    semop(semid, &release, 1);

    // 分离共享内存
    if (shmdt(shmaddr) == -1) 
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
