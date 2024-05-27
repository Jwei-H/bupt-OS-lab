//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_BASE_H
#define BUPT_OS_LAB_BASE_H
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

using namespace std;

string filename;
int fd;
bool opened = false;
char* pargv[4] = { "ls", "-l", nullptr, nullptr };
int openMode = O_RDWR | O_CREAT; // 默认打开模式为读写模式
#endif //BUPT_OS_LAB_BASE_H
