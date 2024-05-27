#include <iostream>
#include<unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

// 定义资源数量和进程数量
const int ResourceType = 3; // 假设有3种资源类型
const int ProcessNum = 5;   // 假设有5个进程

// 银行家算法的数据结构
int *available; // 系统可用资源
int *max_claim; // 每个进程的全部需求
int *allocation; // 每个进程已分配的资源
int *need; // 每个进程还需要的资源

//使用信号量实现进程同步
// 信号量ID
int sem_id;

// 初始化信号量
void init_semaphore() {
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        cerr << "创建信号量失败" << endl;
        exit(1);
    }
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        cerr << "初始化信号量失败" << endl;
        exit(1);
    }
}

// P操作，获取信号量
void P() {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        cerr << "P操作失败" << endl;
        exit(1);
    }
}

// V操作，释放信号量
void V() {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        cerr << "V操作失败" << endl;
        exit(1);
    }
}

// 检查系统是否安全
bool is_safe() {
    vector<int> work(ResourceType, 0);
    for (int i = 0; i < ResourceType; ++i) {
        work[i] = available[i];
    }
    // 标记进程是否已经完成
    vector<bool> finish(ProcessNum, false);
    while (true) {
        bool found = false;
        for (int i = 0; i < ProcessNum; ++i) {
            if (!finish[i]) {
                // 检查是否有足够的资源分配给进程
                bool possible = true;
                for (int j = 0; j < ResourceType; ++j) {
                    if (need[i * ResourceType + j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                // 如果有足够的资源分配给进程，就分配资源
                if (possible) {
                    for (int j = 0; j < ResourceType; ++j) {
                        work[j] += allocation[i * ResourceType + j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    // 检查是否所有进程都已经完成
    for (int i = 0; i < ProcessNum; ++i) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

// 请求资源
bool request_resources(int process_id, vector<int> request) {
    P(); // 进入临界区

    for (int i = 0; i < ResourceType; ++i) {
        if (request[i] > need[process_id * ResourceType + i] || request[i] > available[i]) {
            V(); // 退出临界区
            return false; // 请求的资源超过了需要的资源或系统可用的资源
        }
    }

    // 暂时分配资源
    for (int i = 0; i < ResourceType; ++i) {
        available[i] -= request[i];
        allocation[process_id * ResourceType + i] += request[i];
        need[process_id * ResourceType + i] -= request[i];
    }

    // 检查系统是否安全
    if (is_safe()) {
        // 确认分配
        cout << "资源分配成功" << endl;
        V(); // 退出临界区
        return true;
    } else {
        // 撤销分配
        for (int i = 0; i < ResourceType; ++i) {
            available[i] += request[i];
            allocation[process_id * ResourceType + i] -= request[i];
            need[process_id * ResourceType + i] += request[i];
        }
        cout << "资源分配失败，可能导致死锁" << endl;
        V(); // 退出临界区
        return false;
    }
}

// 释放资源
void release_resources(int process_id) {
    P(); // 进入临界区

    for (int i = 0; i < ResourceType; ++i) {
        available[i] += allocation[process_id * ResourceType + i];
        allocation[process_id * ResourceType + i] = 0;
        need[process_id * ResourceType + i] = max_claim[process_id * ResourceType + i];
    }

    cout << "进程" << process_id << "已释放所有资源" << endl;

    V(); // 退出临界区
}

int main() {
    // 初始化信号量
    init_semaphore();

    // 创建共享内存
    int shm_id = shmget(IPC_PRIVATE, sizeof(int) * ResourceType * (ProcessNum + 3), IPC_CREAT | 0666);
    if (shm_id == -1) {
        cerr << "创建共享内存失败" << endl;
        exit(1);
    }

    // 连接共享内存
    int *shm_ptr = (int *) shmat(shm_id, 0, 0);
    if (shm_ptr == (void *) -1) {
        cerr << "连接共享内存失败" << endl;
        exit(1);
    }

    // 初始化数据结构
    available = shm_ptr;
    max_claim = shm_ptr + ResourceType;
    allocation = max_claim + ResourceType * ProcessNum;
    need = allocation + ResourceType * ProcessNum;

    // 初始化数据
    for (int i = 0; i < ResourceType; ++i) {
        available[i] = 10; // 系统可用资源
    }
    for (int i = 0; i < ResourceType * ProcessNum; ++i) {
        max_claim[i] = 5; // 每个进程的最大需求
        allocation[i] = 0; // 每个进程已分配的资源
        need[i] = max_claim[i]; // 每个进程还需要的资源
    }

    // 创建子进程
    for (int i = 0; i < ProcessNum; ++i) {
        pid_t pid = fork();
        if (pid == 0) { // 子进程
            // 模拟资源请求
            vector<int> request = {1, 0, 2}; // 假设每个进程都请求相同的资源
            while (true) {
                if (request_resources(i, request)) {
                    cout << "进程" << i << "请求资源成功" << endl;
                    break;
                } else {
                    cout << "进程" << i << "请求资源失败," << "等待资源释放" << endl;
                    sleep(1);
                }
            }
            sleep(1);
            release_resources(i);
            exit(0);
        }
    }
    // 等待所有子进程结束
    for (int i = 0; i < ProcessNum; ++i) {
        wait(NULL);
    }
    // 断开共享内存连接
    if (shmdt(shm_ptr) == -1) {
        cerr << "断开共享内存连接失败" << endl;
        exit(1);
    }
    // 删除共享内存
    if (shmctl(shm_id, IPC_RMID, 0) == -1) {
        cerr << "删除共享内存失败" << endl;
        exit(1);
    }
    // 删除信号量
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        cerr << "删除信号量失败" << endl;
        exit(1);
    }
    return 0;
}
