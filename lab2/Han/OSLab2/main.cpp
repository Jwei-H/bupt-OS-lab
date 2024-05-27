#include"Process.h"


const int ProcessNum = 5; // 进程数
const int ResourceType = 3; // 资源种类数
int main() {
    int sem_id =  init_semaphore();
    int size = sizeof(int) * ResourceType * (ProcessNum + 3);
    int shm_id = create_shm(size);

    int *shm_ptr = connect_shm(shm_id);

    // 初始化数据结构
    int *available = shm_ptr;
    int *max_claim = shm_ptr + ResourceType;
    int *allocation = max_claim + ResourceType * ProcessNum;
    int *need = allocation + ResourceType * ProcessNum;

    // 初始化数据
    for (int i = 0; i < ResourceType; ++i) {
        available[i] = 10; // 系统可用资源
    }
    for (int i = 0; i < ResourceType * ProcessNum; ++i) {
        max_claim[i] = 5; // 每个进程的最大需求
        allocation[i] = 0; // 每个进程已分配的资源
        need[i] = max_claim[i]; // 每个进程还需要的资源
    }
    Banker *banker = new Banker();
    banker->setSemId(sem_id);
    banker->setResourceType(ResourceType);
    banker->setNeed(need);
    banker->setAvailable(available);
    banker->setAllocation(allocation);
    banker->setMaxClaim(max_claim);

    create_process(ProcessNum, banker);

    destroy_shm(shm_id, shm_ptr,sem_id);
    return 0;
}
