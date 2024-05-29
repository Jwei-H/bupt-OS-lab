#ifndef RR_H
#define RR_H

#include <iostream>
#include <iomanip>
// 进程结构体
struct myProcess {
    int pid;  // 进程ID
    int burst_time;  // 执行时间
    int waiting_time;  // 等待时间
    int turnaround_time;  // 周转时间
    int remaining_time;  // 剩余执行时间
    int completed;  // 标记进程是否已完成
};
// 轮转调度算法
void rr(myProcess processes[], int n, int quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int time = 0;
    int remaining_processes = n;

    // 初始化剩余执行时间和完成标记
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    // 轮转调度
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed) {
                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].turnaround_time = time;
                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                    processes[i].completed = 1;
                    remaining_processes--;
                }
            }
        }
    }

    // 输出结果
    std::cout << "进程ID\t执行时间\t等待时间\t周转时间\n";
    for (int i = 0; i < n; i++) {
        std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t"
                  << processes[i].waiting_time << "\t\t" << processes[i].turnaround_time << "\n";
    }
    std::cout << "平均等待时间: " << std::fixed << std::setprecision(2)
              << (float)total_waiting_time / n << "\n";
    std::cout << "平均周转时间: " << std::fixed << std::setprecision(2)
              << (float)total_turnaround_time / n << "\n";
}

#endif // RR_H
