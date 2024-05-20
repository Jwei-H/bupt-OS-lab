#include "createFile.h"
#include "updateMod.h"
#include "viewMod.h"
#include "readwrite.h"
#include "viewroad.h"
#include "openmode.h"

int main() 
{
    cout << "**********文件系统调用程序*********" << endl;
    int choice;
    while (true) 
    {
        cout << "\n请选择您的选项\n";
        cout << "1. 设置文件打开模式\n";
        cout << "2. 新建（不存在）或者打开文件\n";
        cout << "3. 读文件\n";
        cout << "4. 写文件\n";
        cout << "5. 给文件权限修改\n";
        cout << "6. 查看文件权限\n";
        cout << "7. 查看文件路径\n";
        cout << "8. 关闭文件\n";
        cout << "9. 退出程序\n";
        cin >> choice;
        switch (choice) 
        {
            case 1:
                SetOpenMode();
                break;
            case 2:
                CreateOpenFileWithMode();
                break;
            case 3:
                ReadFile();
                break;
            case 4:
                WriteFile();
                break;
            case 5:
                ModeFile();
                break;
            case 6:
                ViewMode();
                break;
            case 7:
                ViewRoad();
                break;
            case 8:
                exit();
                break;
            case 9:
                if (opened) 
                {
                    close(fd);
                }
                cout << "程序已退出" << endl;
                return 0;
            default:
                cout << "输入错误！" << endl;
                break;
        }
    }
    return 0;
}
