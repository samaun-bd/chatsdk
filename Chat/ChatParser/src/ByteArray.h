/* 
 * File:   ByteArray.h
 * Author: dipal
 *
 * Created on August 26, 2015, 11:50 AM
 */

#ifndef BYTEARRAY_H
#define	BYTEARRAY_H

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <memory>


namespace imsdk {
    
typedef uint8_t byte;

class ByteArray {
public:
    ByteArray();
    ByteArray(int initialSize);
    ByteArray(const byte* buffer, int bufferLen);
    ByteArray(std::initializer_list<byte> initList);
    ByteArray(const std::string &dataString);
    virtual ~ByteArray();

    int size();
    void push_back(byte b);

    long long getLongLong(const int index, const int len);
    std::string getString(const int index, const int len);
    int getInt(const int index, const int len);

    void appendData(const long long val, const int len);
    void appendData(const int val, const int len);
    void appendData(const std::string &s, const int len);

    void appendByteArray(const std::shared_ptr<ByteArray> &ap);

    std::vector<byte>::iterator begin() {
        return data.begin();
    }

    std::vector<byte>::const_iterator begin() const {
        return data.begin();
    } 

    std::vector<byte>::iterator end() {
        return data.end();
    }

    std::vector<byte>::const_iterator end() const {
        return data.end();
    }

    byte* getDataPtr();

    std::string toString();
    void printByteArray();

    byte& operator[](const int index);

private:
    std::vector<byte> data;

};
}

#endif	/* BYTEARRAY_H */

