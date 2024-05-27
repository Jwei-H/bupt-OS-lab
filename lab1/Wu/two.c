#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define Pro_n 5
#define Fibo_n 40

//斐波那契数列
int fibonacci(int n){
    if(n<=0){
        return -1;
    }
    if(n==1){
        return n;
    }
    return fibonacci(n-1)+fibonacci(n-2);
}

int main(){
    int i = 0;
    pid_t pid ;

    clock_t start, end;
    double cpu_time_used;
    
    printf("Parent process ID: %d\n", getpid());
    start = clock(); // 记录开始时间

    //创建多个进程
    for(i = 0;i < Pro_n;i++ ){
        pid = fork();
        if(pid < 0){
            printf("Wrong Process");
            return 1;
        }
        else if(pid == 0){
            //printf("Child process ID: %d, Parent process ID: %d\n", getpid(), getppid());
            // 计算斐波那契数列
            unsigned long long fib = fibonacci(Fibo_n);
            printf("Child process %d calculated Fibonacci number: %llu\n", getpid(), fib);

            end = clock(); // 记录子进程结束时间
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Child process %d CPU time used: %f seconds\n", getpid(), cpu_time_used);
            
            return 0; // 子进程执行完任务后退出
        }
        
    }
    for(i = 0;i < Pro_n;i++){
        wait(NULL);
    }
    end = clock(); // 记录结束时间

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}