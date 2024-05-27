#ifndef OSLAB2_BANKER_H
#define OSLAB2_BANKER_H

#include "SharedMomery.h"
#include "MessageQueue.h"

#endif //OSLAB2_BANKER_H
class Banker {
private:
    // 定义资源数量
    int ResourceType;
    //所有进程的pid
    vector<int> process_ids;
    // 银行家算法的数据结构
    int *available;    // 系统可用资源
    int *max_claim; // 每个进程的全部需求
    int *allocation; // 每个进程已分配的资源
    int *need; // 每个进程还需要的资源
    int sem_id;
public:
    void setSemId(int semId);

public:
    int getResourceType() const;

    void setResourceType(int resourceType);

    int getProcessNum() const;

    int *getAvailable() const;

    void setAvailable(int *available);

    int *getMaxClaim() const;

    void setMaxClaim(int *maxClaim);

    int *getAllocation() const;

    void setAllocation(int *allocation);

    int *getNeed() const;

    void setNeed(int *need);

    void add_process(int process_id);

    bool is_safe();

    bool request_resources(int process_id, vector<int> request);

    void release_resources(int process_id);
};

