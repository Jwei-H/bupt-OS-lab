#pragma once 
#include <iostream>
#include <vector>
#include "Process.h"
#include "Operation.h" 

using namespace std;
// HRRN 调度算法
void HRRN(std::vector<Process>& processes) {
    int currentTime = 0;
    
    while (!processes.empty()) {
        // 计算响应比
        double maxResponseRatio = -1;
        auto selectedProcessIter = processes.end();

        for (auto it = processes.begin(); it != processes.end(); ++it) {
            auto& process = *it;
            if (process.state != TERMINATED && process.arrivalTime <= currentTime) {
                double responseRatio = (double)(currentTime - process.arrivalTime + process.burstTime) / process.burstTime;
                if (responseRatio > maxResponseRatio) {
                    maxResponseRatio = responseRatio;
                    selectedProcessIter = it;
                }
            }
        }

        // 未找到可执行进程
        if (selectedProcessIter == processes.end()) {
            currentTime++;
            continue;
        }

        auto& selectedProcess = *selectedProcessIter;

        // 打印进程信息
        std::cout << "Executing process ID: " << selectedProcess.processId << ", Arrival Time: " << selectedProcess.arrivalTime
                  << ", Burst Time: " << selectedProcess.burstTime << ", Priority: " << selectedProcess.priority << std::endl;

        // 执行进程
        start_operate(&selectedProcess);
        update_responsetime(&selectedProcess, currentTime - selectedProcess.arrivalTime);
        update_waitingtime(&selectedProcess, currentTime - selectedProcess.arrivalTime);

        // 进程完成
        if (is_finished(&selectedProcess)) {
            update_roundtime(&selectedProcess, currentTime - selectedProcess.arrivalTime);
            processes.erase(selectedProcessIter);
        }

        currentTime++;
    }
}
