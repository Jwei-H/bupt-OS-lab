// 模拟对进程的操作
#include <random>
#include "Operation.h"

void init_process(Process *process)
{
    static int processCount = 0;       // 进程总数
    processCount++;
    process->processId = 1000 + processCount;
    process->waitingTime = 0;
    process->turnaroundTime = 0;
    process->responseTime = 0;
    process->state = READY;
    process->burstTime = rand() % 10 + 1;
    process->priority = 0;
    static int arrivalTime = 0;
    arrivalTime += rand() % 5 ;
    process->arrivalTime = arrivalTime ;//保证到达时间递增
}

void update_watingtime(Process *process, int time)
{
    process->waitingTime += time;
}

void update_roundtime(Process *process, int time)
{
    process->turnaroundTime += time;
}
void update_responsetime(Process *process, int time)
{
    process->responseTime += time;
}
void start_operate(Process *process)
{
    process->state = RUNNING;
    process->burstTime--;
    if (process->burstTime == 0)
    {
        process->state = TERMINATED;
    }
}
bool is_finished(Process *process)
{
    return process->state == TERMINATED;
}
void add_vruntime(Process* process, int time) {
    process->vruntime += time;
}
void des_vruntime(Process* process, int time) {
    process->vruntime -= time;
}