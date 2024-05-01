#include "CFS.h"


void test_CFS();

int main() {
    test_CFS();
    return 0;
}

void test_CFS() {
    std::queue<Process> process_queue;
    for (int i = 0; i < 5; i++) {
        Process process;
        init_process(&process);
        process_queue.push(process);
    }
    CFS(process_queue, 2);
}