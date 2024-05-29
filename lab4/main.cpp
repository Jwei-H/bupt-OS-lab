#include "CFS.h"
#include "FCFS.h"
#include "HRRN.h"
#include "sjf.h"
#include "RR.h"
#include <memory>
void test_CFS();
void test_FCFS();
void test_HRRN();
void test_sjf();
void test_RR();
int main()
{
    test_CFS();
    test_FCFS();
    test_HRRN();
    test_sjf();
    test_RR();
}

void test_CFS()
{
    std::queue<Process> process_queue; 
    for (int i = 0; i < 5; i++)
    {
        std::shared_ptr<Process> process = std::make_shared<Process>();
        init_process(process.get());
        process_queue.push(*process);
    }
    CFS(process_queue, 4);
}
void test_FCFS()
{
    vector<Process> processes;
    for (int i = 0; i < 5; i++)
    {
        Process process;
        init_process(&process);
        processes.push_back(process);
    }
    FCFS(processes);
}

void test_HRRN()
{
    vector<Process> processes;
    for (int i = 0; i < 5; i++)
    {
        Process process;
        init_process(&process);
        processes.push_back(process);
    }
    HRRN(processes);
}
void test_sjf(){
    // 进程数量
    int n;
    std::cout << "请输入进程数量: ";
    std::cin >> n;

    // 进程数组
    myProcess processes[n];

    // 输入每个进程的执行时间
    for (int i = 0; i < n; i++) {
        std::cout << "请输入进程 " << i + 1 << " 的执行时间: ";
        std::cin >> processes[i].burst_time;
        processes[i].pid = i + 1;
    }

    // 执行短作业优先调度算法
    std::cout << "\n短作业优先 (SJF):\n";
    sjf(processes, n);
}
void test_RR() {
    // 进程数量
    int n;
    std::cout << "请输入进程数量: ";
    std::cin >> n;

    // 进程数组
    myProcess processes[n];

    // 输入每个进程的执行时间
    for (int i = 0; i < n; i++) {
        std::cout << "请输入进程 " << i + 1 << " 的执行时间: ";
        std::cin >> processes[i].burst_time;
        processes[i].pid = i + 1;
    }

    // 执行轮转调度算法
    int quantum;
    std::cout << "\n请输入时间片大小: ";
    std::cin >> quantum;
    std::cout << "\n轮转调度 (RR):\n";
    rr(processes, n, quantum);
}
