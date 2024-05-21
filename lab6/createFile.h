//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_CREATEFILE_H
#define BUPT_OS_LAB_CREATEFILE_H

#include "base.h"

// CreateOpenFileWithMode 函数用于创建或打开文件，并应用选择的打开模式
void CreateOpenFileWithMode()
{
    cout << "请输入文件名" << endl;
    cin >> filename;

    // 设置文件权限掩码
    umask(0000);

    // 使用用户选择的模式打开文件
    fd = open(filename.c_str(), openMode, 0666);

    // 动态分配内存并复制文件名
    pargv[2] = (char*)malloc(50);
    strcpy(pargv[2], filename.c_str());

    // 判断文件是否成功打开
    if (fd < 0)
    {
        cout << "打开失败" << endl;
    }
    else
    {
        opened = true;
        cout << "打开成功" << endl;
    }
}

#endif //BUPT_OS_LAB_CREATEFILE_H
