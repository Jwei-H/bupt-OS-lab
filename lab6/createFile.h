//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_CREATEFILE_H
#define BUPT_OS_LAB_CREATEFILE_H

#include "base.h"

void CreateOpenFile() {
    cout << "请输入文件名" << endl;
    cin >> filename;
    umask(0000);
    fd = open(filename.c_str(), openMode, 0666);
    pargv[2] = (char*)malloc(50);
    strcpy(pargv[2], filename.c_str());
    if (fd < 0) {
        cout << "打开失败" << endl;
    } else {
        opened = true;
        cout << "打开成功" << endl;
    }
}

#endif //BUPT_OS_LAB_CREATEFILE_H
