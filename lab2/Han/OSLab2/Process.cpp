#include "Process.h"

void create_process(int ProcessNum, Banker *banker) {
    for (int i = 0; i < ProcessNum; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(1);
        }
        if (pid == 0) {
            process_run(banker);
            exit(0);
        }
    }
}

void process_run(Banker *banker) {
    int pid = getpid();
    banker->add_process(pid);
    vector<int> request = {1, 0, 2}; // 假设每个进程都请求相同的资源
    while (true) {
        if (banker->request_resources(pid, request)) {
            cout << "进程" << pid << "请求资源成功" << endl;
            break;
        } else {
            cout << "进程" << pid << "请求资源失败," << "等待资源释放" << endl;
//            create_msg();
//            struct msgbuf msg;
//
//            if (msgrcv(meg_id, &msg, sizeof(msg.mtext), 0, 0) == -1) {
//                perror("msgrcv");
//            }
//            std::cout << "Received message: " << msg.mtext << std::endl;
            sleep(1);
        }
    }
    sleep(1);
    banker->release_resources(pid);
}