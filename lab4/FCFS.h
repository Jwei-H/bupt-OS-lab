#pragma once
#include "Process.h"
#include "Operation.h"
#include <iostream>
#include <vector>

using namespace std;

void FCFS(vector<Process>& processes) {
    int currentTime = 0;
    int n = processes.size();

    while (n > 0) {
        // 查找下一个到达时间不大于当前时间的进程
        int nextProcessIndex = -1;
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime) {
                nextProcessIndex = i;
                break;
            }
        }

        if (nextProcessIndex != -1) {
            auto& currentProcess = processes[nextProcessIndex];
            
            // 打印进程信息
            std::cout << "Executing Process ID: " << currentProcess.processId 
                      << " Arrival Time: " << currentProcess.arrivalTime 
                      << " Burst Time: " << currentProcess.burstTime << std::endl;
                      
            // 开始执行进程
            start_operate(&currentProcess);
            update_responsetime(&currentProcess, currentTime - currentProcess.arrivalTime);
            update_waitingtime(&currentProcess, currentTime - currentProcess.arrivalTime);

            // 进程完成
            if (is_finished(&currentProcess)) {
                update_roundtime(&currentProcess, currentTime - currentProcess.arrivalTime);
                processes.erase(processes.begin() + nextProcessIndex);
                n--;
            }
        }

        // 更新当前时间
        currentTime++;
    }
}
