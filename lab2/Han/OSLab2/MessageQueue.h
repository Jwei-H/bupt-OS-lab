#ifndef OSLAB2_MESSAGEQUEUE_H
#define OSLAB2_MESSAGEQUEUE_H

#include <iostream>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#endif //OSLAB2_MESSAGEQUEUE_H


extern int meg_id;

struct MsgBuf {
    long mtype;
    char mtext[256];
};

extern int create_msg();

extern void destroy_msg();
