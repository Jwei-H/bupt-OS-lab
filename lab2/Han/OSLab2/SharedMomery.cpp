#include "SharedMomery.h"

int init_semaphore() {
    int sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        cerr << "创建信号量失败" << endl;
        exit(1);
    }
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        cerr << "初始化信号量失败" << endl;
        exit(1);
    }
    return sem_id;
}

void P(int sem_id) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        cerr << "P操作失败" << endl;
        exit(1);
    }
}

void V(int sem_id) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        cerr << "V操作失败" << endl;
        exit(1);
    }
}

int create_shm(int size) {
    int shm_id = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
    if (shm_id == -1) {
        cerr << "创建共享内存失败" << endl;
        exit(1);
    }
    return shm_id;
}

int *connect_shm(int shm_id) {
    int *shm_ptr = (int *) shmat(shm_id, 0, 0);
    if (shm_ptr == (void *) -1) {
        cerr << "连接共享内存失败" << endl;
        exit(1);
    }
    return shm_ptr;
}

void destroy_shm(int shm_id, int *shm_ptr,int sem_id) {
    if (shmdt(shm_ptr) == -1) {
        cerr << "断开共享内存连接失败" << endl;
        exit(1);
    }
    if (shmctl(shm_id, IPC_RMID, 0) == -1) {
        cerr << "删除共享内存失败" << endl;
        exit(1);
    }
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        cerr << "删除信号量失败" << endl;
        exit(1);
    }
}
