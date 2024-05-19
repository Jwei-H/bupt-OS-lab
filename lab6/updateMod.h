//
// Created by han on 5/19/24.
//

#ifndef BUPT_OS_LAB_UPDATEMOD_H
#define BUPT_OS_LAB_UPDATEMOD_H
#include "base.h"



void ModeFile() {
    if (!opened) {
        cout << "首先需要打开文件" << endl;
        return;
    }
    int mode;
    cout << "输入新的模式" << endl;
    cin >> mode;
    int mode_u = mode / 100;
    int mode_g = mode / 10 % 10;
    int mode_o = mode % 10;
    mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;   // 八进制转换
    int returnnum = chmod(filename.c_str(), mode);
    if (returnnum == -1) {
        cout << "改变模式失败！" << endl;
    } else {
        cout << "改变模式成功！" << endl;
    }
}

#endif //BUPT_OS_LAB_UPDATEMOD_H
