#pragma once
#include "Process.h"
#include "Operation.h"
#include <queue>
#include <iostream>

struct Compare {
    bool operator()(const Process* a, const Process* b) const {
        return a->vruntime > b->vruntime;
    }
};

void CFS(std::queue<Process> process_queue, int time_slice){
    int current_time = 0;
    int process_count = process_queue.size();
    std::priority_queue<Process*, std::vector<Process*>, Compare> pq;
    std::queue<Process> finished_queue;
    while(true){
        // 将到达时间小于等于当前时间的进程加入优先队列
        while(!process_queue.empty() && process_queue.front().arrivalTime <= current_time){
            Process* process = new Process(process_queue.front());
            process_queue.pop();
            pq.push(process);
        }
        // 优先队列为空，且所有进程都已经执行完毕
        if(pq.empty() && process_queue.empty()){
            break;
        }
        // 优先队列为空，但还有进程未到达
        if(pq.empty()){
            current_time = process_queue.front().arrivalTime;
            continue;
        }
        Process* process = pq.top();
        // 记录等待时间
        update_watingtime(process, current_time - process->arrivalTime);
        // 记录响应时间
        if(process->responseTime == 0){
            update_responsetime(process, current_time - process->arrivalTime);
        }
        process->state = RUNNING;
        while(true){
        // 运行时间小于时间片
            if(process->burstTime <= time_slice){
                current_time += process->burstTime;
                update_roundtime(process, current_time - process->arrivalTime);
                process->burstTime = 0;
                process->state = TERMINATED;
                finished_queue.push(*process);
                pq.pop();
                delete process;
                break;
            }
            // 运行时间大于时间片
            else{
                current_time += time_slice;
                process->burstTime -= time_slice;
                add_vruntime(process, time_slice);
                pq.pop();
                pq.push(process); // 将process指针重新插入到队列中
                if(pq.top()->processId != process->processId){
                    process->state = READY;
                    process->arrivalTime = current_time; // 使用一个新的变量记录每次被调度的时间
                    break;
                }
            }
        }
 
    }
    // 输出结果
    while(!finished_queue.empty()){
        Process process = finished_queue.front();
        finished_queue.pop();
        std::cout << "Process ID: " << process.processId << std::endl;
        std::cout << "Waiting Time: " << process.waitingTime << std::endl;
        std::cout << "Turnaround Time: " << process.turnaroundTime << std::endl;
        std::cout << "Response Time: " << process.responseTime << std::endl;
        std::cout << std::endl;
    }

}
