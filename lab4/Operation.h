#pragma once
#include "Process.h"

void init_process(Process* process);
void update_waitingtime(Process* process,int time);
void update_roundtime(Process* process,int time);
void update_responsetime(Process* process,int time);
void start_operate(Process* process);
bool is_finished(Process* process);
void add_vruntime(Process* process, int time);
void des_vruntime(Process* process, int time);