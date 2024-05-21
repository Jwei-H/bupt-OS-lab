#ifndef BUPT_OS_LAB_RENAME_H
#define BUPT_OS_LAB_RENAME_H

#include "base.h"

// 检查文件是否存在
bool FileExists(const string& filePath) {
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}
// 重命名文件
void RenameFile(){
    const string oldname = filename;
    string newname;
    cout << "请输入文件新名称：" << endl;
    cin >> newname;
    if (FileExists(newname)) {
        cout << "目标文件已存在。请选择如何处理冲突:" << endl;
        cout << "1. 覆盖目标文件" << endl;
        cout << "2. 放弃重命名" << endl;
        cout << "3. 输入新的文件名" << endl;
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                // 覆盖目标文件
                if (rename(oldname.c_str(), newname.c_str()) == 0) {
                    cout << "文件重命名成功，目标文件已覆盖。" << endl;
                } else {
                    perror("重命名失败");
                }
                break;

            case 2:
                // 放弃重命名
                cout << "放弃重命名。" << endl;
                break;

            case 3:
                // 输入新的文件名
                {
                    string newFileName;
                    cout << "请输入新的文件名:" << endl;
                    cin >> newFileName;

                    if (rename(oldname.c_str(), newname.c_str()) == 0) {
                        cout << "文件重命名成功，新文件名为: " << newFileName << endl;
                    } else {
                        perror("重命名失败");
                    }
                }
                break;

            default:
                cout << "无效选择，放弃重命名。" << endl;
                break;
        }
    } else {
         if (0 == rename(oldname.c_str(),newname.c_str())) {
        cout << "文件重命名成功" << endl;
    } else {
        perror("rename");
    }
    }
   
}

#endif //BUPT_OS_LAB_RENAME_H