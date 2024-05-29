#include "createFile.h"
#include "updateMod.h"
#include "viewMod.h"
#include "readwrite.h"
#include "viewroad.h"
#include "openmode.h"
#include "rename.h"
#include "encryption.h"
int main() 
{
    cout << "**********文件系统调用程序*********" << endl;
    int choice;
    std::string filename, key;
    while (true) 
    {
        cout << "\n请选择您的选项\n";
        cout << "1. 新建（不存在）或者打开文件\n";
        cout << "2. 设置文件打开模式\n";
        cout << "3. 读文件\n";
        cout << "4. 写文件\n";
        cout << "5. 修改文件权限\n";
        cout << "6. 查看文件权限\n";
        cout << "7. 查看文件路径\n";
        cout << "8. 重命名文件\n";
        cout << "9. 关闭文件\n";
        cout << "10. 退出程序\n";
        cout<<"11.加密文件";
        cout<<"12.解密文件";
        cin >> choice;
        switch (choice) 
        {
            case 1:
                CreateOpenFileWithMode();
                break;
            case 2:
                SetOpenMode();
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
                RenameFile();
            case 9:
                exit();
                break;
            case 10:
                if (opened) 
                {
                    close(fd);
                }
                cout << "程序已退出" << endl;
                return 0;
            case 11:
                std::cout << "请输入要加密的文件名：";
                std::cin >> filename;
                std::cout << "请输入加密密钥：";
                std::cin >> key;
                encryptFile(filename, key);
                break;
            case 12:
                std::cout << "请输入要解密的文件名：";
                std::cin >> filename;
                std::cout << "请输入解密密钥：";
                std::cin >> key;
                decryptFile(filename, key);
                break;
            default:
                cout << "输入错误！" << endl;
                break;
        }
    }
    return 0;
}
