/* 
 * File:   ByteArray.cpp
 * Author: dipal
 * 
 * Created on August 26, 2015, 11:50 AM
 */

#include "ByteArray.h"
#include <sstream>
#include <deque>

namespace imsdk {
ByteArray::ByteArray() {
    data.reserve(64);
}

ByteArray::~ByteArray() {
    data.clear();
}

ByteArray::ByteArray(int initialSize) {
    data = std::vector<byte>(initialSize);
}

ByteArray::ByteArray(const byte* buffer, int bufferLen) {
    data = std::vector<byte>(bufferLen);
    std::copy(buffer, buffer+bufferLen, data.begin());
}

ByteArray::ByteArray(std::initializer_list<byte> initList) {
    data = initList;
}

ByteArray::ByteArray(const std::string &dataString) : ByteArray((const byte*)dataString.data(), (int)dataString.size()) {
}

int ByteArray::size() {
    return (int) data.size();
}

void ByteArray::push_back(byte b) {
    data.push_back(b);
}

byte& ByteArray::operator[](const int index) {
    return data[index];
}

long long ByteArray::getLongLong(const int index, const int len) {
    long long ret = 0;
    int t_index = index;
    for (int i = 0; i < len; i++, t_index++) {
        ret |= ((long long) data[t_index]) << ((len - i - 1)*8);
    }

    return ret;
}

std::string ByteArray::getString(const int index, const int len) {
    std::string ret;
    int t_index = index;
    for (int i = 0; i < len; i++, t_index++) {
        ret.push_back(data[t_index]);
    }

    return ret;
}

int ByteArray::getInt(const int index, const int len) {
    int ret = 0;
    int t_index = index;
    for (int i = 0; i < len; i++, t_index++) {
        ret |= ((int) data[t_index]) << ((len - i - 1)*8);
    }

    return ret;
}

void ByteArray::appendData(const long long val, const int len) {
    for (int i = 0; i < len; i++) {
        data.push_back(val >> ((len - i - 1)*8));
    }
}

void ByteArray::appendData(const int val, const int len) {
    for (int i = 0; i < len; i++) {
        data.push_back(val >> ((len - i - 1)*8));
    }
}

void ByteArray::appendData(const std::string &s, const int len) {
    for (int i = 0; i < len; i++) {
        data.push_back(s[i]);
    }
}

void ByteArray::appendByteArray(const std::shared_ptr<ByteArray> &ap) {
    data.insert(data.end(), ap->begin(), ap->end());
}

byte* ByteArray::getDataPtr() {
    return data.data();
}

std::string ByteArray::toString() {
    std::stringstream sin;
    sin << "{";

    for (std::vector<byte>::size_type i = 0; i < data.size(); i++) {
        if (i) sin << ", ";
        sin << (int) data[i];
    }

    sin << "}";

    return sin.str();
}

void ByteArray::printByteArray() {
    std::cout << toString() << std::endl;
}
}
