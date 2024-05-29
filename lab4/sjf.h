
#ifndef SJF_H
#define SJF_H

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

// 短作业优先调度算法
void sjf(myProcess processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // 对进程按照执行时间进行排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                myProcess temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // 计算等待时间和周转时间
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            processes[i].waiting_time = 0;
        } else {
            processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        }
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
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

#endif // SJF_H
