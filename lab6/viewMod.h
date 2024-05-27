//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_VIEWMOD_H
#define BUPT_OS_LAB_VIEWMOD_H

#include "base.h"

void exit() {
    close(fd);
    opened = false;
}

void ViewMode() {
    if (!opened) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    cout << "文件权限为：";
    int returnnum = execv("/bin/ls", pargv);
    if (returnnum == -1) {
        cout << "查看失败" << endl;
    } else {
        cout << "文件权限为：" << endl;
    }
}

#endif //BUPT_OS_LAB_VIEWMOD_H
