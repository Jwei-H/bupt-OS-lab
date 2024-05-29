
#include "encryption.h"

void processFile(const std::string& filename, const std::string& key) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cerr << "错误：无法打开文件：" << filename << std::endl;
        return;
    }

    std::string tempFilename = filename + ".tmp";
    std::ofstream outfile(tempFilename, std::ios::binary);
    if (!outfile) {
        std::cerr << "错误：无法创建临时文件：" << tempFilename << std::endl;
        return;
    }

    char ch;
    size_t keyIndex = 0;
    while (infile.get(ch)) {
        ch ^= key[keyIndex]; // 使用密钥进行异或操作
        outfile.put(ch);
        keyIndex = (keyIndex + 1) % key.size();
    }

    infile.close();
    outfile.close();

    // 用临时文件替换原始文件
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "错误：无法删除原始文件：" << filename << std::endl;
    } else if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
        std::cerr << "错误：无法重命名临时文件：" << tempFilename << std::endl;
    }
}

void encryptFile(const std::string& filename, const std::string& key) {
    processFile(filename, key);
    std::cout << "文件已加密：" << filename << std::endl;
}

void decryptFile(const std::string& filename, const std::string& key) {
    processFile(filename, key);
    std::cout << "文件已解密：" << filename << std::endl;
}
