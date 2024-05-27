#include"MessageQueue.h"

int meg_id;

int create_msg() {
    meg_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (meg_id == -1) {
        perror("msgget error");
        return -1;
    }
    return meg_id;
}

void destroy_msg() {
    if (msgctl(meg_id, IPC_RMID, NULL) == -1) {
        perror("msgctl error");
    }
}
