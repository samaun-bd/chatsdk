#include <sstream>

#include "DataEncryption.h"
#include "ResourceManager.h"
#include "HashAlgorithm.h"
#include "ChatParser.h"

namespace ipvsdk {
namespace security {

std::string DataEncryption::getSessionlessKey(std::string ipAddress, long long ringId)
{
    std::vector<std::string> ipOctets = imsdk::ChatParser::getSplittedString(ipAddress, '.');

    long long ipOctetsProduct{1};
    for(auto ipOctet:ipOctets) {
        int octetValue = imsdk::ResourceManager::toStringToInt(ipOctet);
        if(octetValue > 0) {
            ipOctetsProduct *= octetValue;
        }
    }

    long long ipOctetsProductWithSalt = ipOctetsProduct * KEY_SALT;
    long long finalKey = ipOctetsProductWithSalt ^ ringId;

    std::string finalKeyStr = HashAlgorithm::sha1(imsdk::ResourceManager::getInstance().toLongToString(finalKey));

    return finalKeyStr;
}

imsdk::ByteArray DataEncryption::encryptMessage(imsdk::ByteArray &data, imsdk::ByteArray &key, int startIndex)
{
    imsdk::ByteArray encryptedData(data.size());
    for (size_t i = 0, j = 0; i < data.size(); i++, j = (j + 1) % key.size())
    {
        encryptedData[i] = (i>=startIndex) ? encrypt(data[i], key[j]) : data[i];
    }
    return encryptedData;
}

imsdk::ByteArray DataEncryption::decryptMessage(imsdk::ByteArray &data, imsdk::ByteArray &key, int startIndex)
{
    imsdk::ByteArray decryptedData(data.size());
    for (size_t i = 0, j = 0; i < data.size(); i++, j = (j + 1) % key.size())
    {
        decryptedData[i] = (i>=startIndex) ? decrypt(data[i], key[j]) : data[i];
    }
    return decryptedData;
}        

char DataEncryption::encrypt(char toEncrypt, char encryptKey)
{
    int encryptSource = toEncrypt;
    int digest = encryptSource + 128;
    digest = (digest + (int)encryptKey + salt) % 256;
    return (char) digest;
}

char DataEncryption::decrypt(char toDecrypt, char decryptKey)
{
    int decryptSource = toDecrypt;
    int data = decryptSource + 128;
    data = (data - (int)decryptKey - salt) % 256;
    return (char) data;
}    
}
}

