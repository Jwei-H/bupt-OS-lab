#ifndef BUPT_OS_LAB_VIEWROAD_H
#define BUPT_OS_LAB_VIEWROAD_H

#include "base.h"
#include <limits.h>

// ViewRoad 函数实现查看文件的创建路径
void ViewRoad() 
{
    // 检查文件是否已打开
    if (!opened) 
    {
        cout << "首先需要打开文件" << endl;
        return;
    }

    // 定义一个字符数组，用于存储文件的绝对路径
    char absPath[PATH_MAX];

    // 调用 realpath 函数获取文件的绝对路径
    // realpath 函数将文件名转换为绝对路径，并存储在 absPath 中
    if (realpath(filename.c_str(), absPath) != NULL) 
    {
        // 如果成功获取绝对路径，打印路径
        cout << "文件的绝对路径为：" << absPath << endl;
    } 
    else 
    {
        // 如果获取绝对路径失败，打印错误信息
        cout << "获取绝对路径失败" << endl;
    }
}

#endif //BUPT_OS_LAB_VIEWROAD_H
