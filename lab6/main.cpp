


#include "createFile.h"
#include "updateMod.h"
#include "viewMod.h"
#include "readwrite.h"


int main() {
    cout << "**********文件系统调用程序*********" << endl;
    int choice;
    while (true) {
        cout << "\n请选择您的选项\n";
        cout << "1.新建（不存在）或者打开文件\n";
        cout << "2.读文件\n";
        cout << "3.写文件\n";
        cout << "4.给文件权限修改\n";
        cout << "5.查看文件权限\n";
        cout << "6.关闭文件\n";
        cin >> choice;
        switch (choice) {
            case 1:
                CreateOpenFile();
                break;
            case 2:
                ReadFile();
                break;
            case 3:
                WriteFile();
                break;
            case 4:
                ModeFile();
                break;
            case 5:
                ViewMode();
                break;
            case 6:
                exit();
                break;
            default:
                cout << "输入错误！" << endl;
                break;
        }
    }
    return 0;
}
