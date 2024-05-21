//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_READWRITE_H
#define BUPT_OS_LAB_READWRITE_H

#include "base.h"


void WriteFile() {
    if (!opened) {
        cout << "首先需要打开文件" << endl;
        return;
    }

    // 先读取文件内容
    char readBuffer[1024];
    memset(readBuffer, 0, sizeof(readBuffer));
    lseek(fd, 0, SEEK_SET);
    int returnnum = read(fd, readBuffer, 1024);
    if (returnnum != -1) {
        cout << "文件当前内容为：" << endl;
        cout << readBuffer << endl;
    } else {
        cout << "读取失败" << endl;
    }

    int writeMode= O_WRONLY | O_CREAT | O_APPEND;
    if(openMode == writeMode) {
        cout << "追加模式" << endl;
    }
    writeMode = O_RDWR | O_CREAT;
    if(openMode == writeMode) {
        cout << "覆写模式" << endl;
        ftruncate(fd, 0);  // 清空文件
        lseek(fd, 0, SEEK_SET);  // 重新定位到文件开头
    }
    // 再写入新的内容
    string buffer;
    cout << "请输入新的文件内容" << endl;
    cin >> buffer;
    returnnum = write(fd, buffer.c_str(), buffer.length());
    if (returnnum != -1) {
        cout << "写入成功！" << endl;
    } else {
        cout << "写入失败！" << endl;
    }
}

void ReadFile() {
    if (!opened) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    // lseek() 定位一个已经打开的文件
    lseek(fd, 0, SEEK_SET);
    int returnnum = read(fd, buffer, 1024);
    if (returnnum != -1) {
        cout << "文件内容为：" << endl;
        cout << buffer << endl;
    } else {
        cout << "读取失败" << endl;
    }
}

#endif //BUPT_OS_LAB_READWRITE_H
