#ifndef IPVSDK_SECURITY_DATAENCRYPTION_H_
#define IPVSDK_SECURITY_DATAENCRYPTION_H_
#include <string>
#include <unordered_map>
#include <string.h>
#include "sha1.h"
#include "ByteArray.h"

namespace ipvsdk {
namespace security {

class DataEncryption {
public:
    static imsdk::ByteArray encryptMessage(imsdk::ByteArray &data, imsdk::ByteArray &key, int startIndex = 0);
    static imsdk::ByteArray decryptMessage(imsdk::ByteArray &data, imsdk::ByteArray &key, int startIndex = 0);
    static std::string getSessionlessKey(std::string ipAddress, long long ringId);
private:
    static char encrypt(char toEncrypt, char encryptKey);
    static char decrypt(char toDecrypt, char decryptKey);
    
    static const int salt = 50;
    static const int KEY_SALT = 97;
};
}
}


#endif /* IPVSDK_SECURITY_DATAENCRYPTION_H_ */

