#ifndef IPVSDK_SECURITY_HASHALGORITHM_H_
#define IPVSDK_SECURITY_HASHALGORITHM_H_
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <cstring>
#include "sha1.h"

namespace ipvsdk {
namespace security {
class HashAlgorithm
{
public:
    static std::string sha1(std::string key);
private:
    static char hexToChar(int val);
};
}
}


#endif /* IPVSDK_SECURITY_HASHALGORITHM_H_ */

