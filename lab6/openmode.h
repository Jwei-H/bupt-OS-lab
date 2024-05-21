#ifndef BUPT_OS_LAB_OPENMODE_H
#define BUPT_OS_LAB_OPENMODE_H

#include "base.h"

// SetOpenMode 函数用于设置文件的打开模式
void SetOpenMode() 
{
    int choice;
    cout << "\n请选择文件打开模式\n";
    cout << "1. 只读\n";
    cout << "2. 只写\n";
    cout << "3. 读写\n";
    cout << "4. 追加\n";
    cin >> choice;

    // 根据用户选择设置相应的文件打开模式
    switch (choice) 
    {
        case 1:
            openMode = O_RDONLY; // 只读模式
            break;
        case 2:
            openMode = O_WRONLY | O_CREAT; // 只写模式，如果文件不存在则创建
            break;
        case 3:
            openMode = O_RDWR | O_CREAT; // 读写模式，如果文件不存在则创建
            break;
        case 4:
            openMode = O_WRONLY | O_CREAT | O_APPEND; // 追加模式，如果文件不存在则创建
            break;
        default:
            cout << "输入错误，使用默认读写模式" << endl;
            openMode = O_RDWR | O_CREAT; // 默认读写模式
            break;
    }

    cout << "文件打开模式已设置" << endl;
}

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

#endif //BUPT_OS_LAB_OPENMODE_H
