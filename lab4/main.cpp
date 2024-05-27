#include "CFS.h"
#include "FCFS.h"
#include "HRRN.h"
#include <memory>
void test_CFS();
void test_FCFS();
void test_HRRN();

int main()
{
    test_CFS();
    test_FCFS();
    test_HRRN();
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
    CFS(process_queue, 2);
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