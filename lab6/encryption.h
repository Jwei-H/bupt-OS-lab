#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

// 加密和解密函数声明
void encryptFile(const std::string& filename, const std::string& key);
void decryptFile(const std::string& filename, const std::string& key);

#endif // ENCRYPTION_H
