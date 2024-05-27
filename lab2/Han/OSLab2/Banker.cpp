#include <cstring>
#include "Banker.h"

bool Banker::is_safe() {

    vector<int> work(ResourceType, 0);
    for (int i = 0; i < ResourceType; ++i) {
        work[i] = available[i];
    }
    // 标记进程是否已经完成
    vector<bool> finish(process_ids.size(), false);
    while (true) {
        bool found = false;
        for (int i = 0; i < process_ids.size(); ++i) {
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
    for (int i = 0; i < process_ids.size(); ++i) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

int Banker::getResourceType() const {
    return ResourceType;
}

int Banker::getProcessNum() const {
    return process_ids.size();
}


int *Banker::getAvailable() const {
    return available;
}

void Banker::setAvailable(int *available) {
    Banker::available = available;
}

int *Banker::getMaxClaim() const {
    return max_claim;
}

void Banker::setMaxClaim(int *maxClaim) {
    max_claim = maxClaim;
}

int *Banker::getAllocation() const {
    return allocation;
}

void Banker::setAllocation(int *allocation) {
    Banker::allocation = allocation;
}

int *Banker::getNeed() const {
    return need;
}

void Banker::setNeed(int *need) {
    Banker::need = need;
}

void Banker::setResourceType(int ResourceType) {
    Banker::ResourceType = ResourceType;
}

bool Banker::request_resources(int process_id, vector<int> request) {
    P(sem_id); // 进入临界区
    int process_no;
    for(int i = 0; i < process_ids.size(); ++i) {
        if (process_ids[i] == process_id) {
            process_no = i;
            break;
        }
    }
    for (int i = 0; i < ResourceType; ++i) {
        if (request[i] > need[process_no * ResourceType + i] || request[i] > available[i]) {
            V(sem_id); // 退出临界区
            return false; // 请求的资源超过了需要的资源或系统可用的资源
        }
    }

    // 暂时分配资源
    for (int i = 0; i < ResourceType; ++i) {
        available[i] -= request[i];
        allocation[process_no * ResourceType + i] += request[i];
        need[process_no * ResourceType + i] -= request[i];
    }

    // 检查系统是否安全
    if (is_safe()) {
        // 确认分配
        cout << "资源分配成功" << endl;
        V(sem_id); // 退出临界区
        return true;
    } else {
        // 撤销分配
        for (int i = 0; i < ResourceType; ++i) {
            available[i] += request[i];
            allocation[process_no * ResourceType + i] -= request[i];
            need[process_no * ResourceType + i] += request[i];
        }
        cout << "资源分配失败，可能导致死锁" << endl;
        V(sem_id); // 退出临界区
        return false;
    }
}

void Banker::release_resources(int process_id) {
    P(sem_id); // 进入临界区
    int process_no;
    for(int i = 0; i < process_ids.size(); ++i) {
        if (process_ids[i] == process_id) {
            process_no = i;
            break;
        }
    }
    for (int i = 0; i < ResourceType; ++i) {
        available[i] += allocation[process_no * ResourceType + i];
        allocation[process_no * ResourceType + i] = 0;
        need[process_no * ResourceType + i] = max_claim[process_no * ResourceType + i];
    }

    cout << "进程" << process_id << "已释放所有资源" << endl;

    V(sem_id); // 退出临界区

    //使用消息队列通知进程资源已释放
//    create_msg();
//    struct msgbuf msg;
//    msg.mtype = 1;  // 设置消息类型
//    strncpy(msg.mtext, "资源已释放", sizeof(msg.mtext) - 1);
//    msg.mtext[sizeof(msg.mtext) - 1] = '\0';  // 确保字符串正确终止
//
//    if (msgsnd(meg_id, &msg, strlen(msg.mtext) + 1, 0) == -1) {
//        perror("msgsnd");
//    }

}

void Banker::add_process(int process_id) {
    process_ids.push_back(process_id);
}

void Banker::setSemId(int semId) {
    sem_id = semId;
}


