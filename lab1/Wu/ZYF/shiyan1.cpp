#include <iostream>
#include <unistd.h> // 包含 fork(), sleep() 等系统调用的头文件
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> // 包含 kill() 函数的头文件

using namespace std;

// 全局变量用于进程同步
volatile int flag = 0;

// 信号处理函数，用于进程撤销
void sigHandler(int signum) 
{
    cout << "Received signal " << signum << ", exiting..." << endl;
    exit(signum);
}

int main() 
{
    pid_t pid_sleep, pid_wake;

    // 进程的创建
    pid_sleep = fork(); // 创建用于睡眠的子进程
    if (pid_sleep == 0) 
    { // 子进程1
        // 进程睡眠实验
        cout << "Child Process for sleeping (PID: " << getpid() << ") is going to sleep" << endl;
        sleep(3); // 子进程睡眠3秒
        cout << "Child Process for sleeping (PID: " << getpid() << ") wakes up" << endl;
        exit(0); // 子进程结束
    }

    pid_wake = fork(); // 创建用于唤醒的子进程
    if (pid_wake == 0) 
    { // 子进程2
        // 进程同步实验
        // 用于进程同步，实现交替打印
        for (int i = 0; i < 5; ++i) 
        {
            while (flag != 1); // 等待flag为1，表示可以打印
            cout << "Child Process for waking (PID: " << getpid() << ") prints " << i << endl;
            flag = 0; // 设置flag为0，表示打印完成
        }
        exit(0); // 子进程结束
    }

    // 父进程
    // 进程撤销实验
    // 注册信号处理函数，以便父进程可以终止子进程
    signal(SIGINT, sigHandler);

    // 等待子进程结束
    waitpid(pid_sleep, NULL, 0);
    cout << "Child Process for sleeping (PID: " << pid_sleep << ") finished" << endl;

    // 终止子进程2的执行
    cout << "Terminating Child Process for waking (PID: " << pid_wake << ")" << endl;
    kill(pid_wake, SIGINT);

    // 等待子进程结束
    waitpid(pid_wake, NULL, 0);
    cout << "Child Process for waking (PID: " << pid_wake << ") finished" << endl;

    return 0;
}
