#include "HashAlgorithm.h"

namespace ipvsdk {
namespace security {

char HashAlgorithm::hexToChar(int val)
{
    if (val < 10) return '0'+val;
    return 'a'+(val-10);
}

std::string HashAlgorithm::sha1(std::string key)
{
    SHA1* sha1;
    unsigned char* digest;
    
    char *text = new char [key.length()+1];
    std::strcpy (text, key.c_str());
    
    sha1 = new SHA1();
    sha1->addBytes( text, std::strlen( text ) );
    digest = sha1->getDigest();
    
    std::string hexValue;
    for (int i=0; i<20; i++)
    {
        hexValue.push_back(hexToChar(digest[i]>>4));
        hexValue.push_back(hexToChar(digest[i] & 0xf));
    }

    delete sha1;
    free( digest );
    
    return hexValue;
}

}
}