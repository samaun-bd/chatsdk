/* 
 * File:   chatparsertest.cpp
 * Author: dipal
 *
 * Created on Jul 26, 2015, 10:16:16 AM
 */

#include <stdlib.h>
#include <iostream>
#include <src/ChatParser.h>

#include "src/PacketDTO.h"
/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "chatparsertest test 1" << std::endl;
    
    ByteArray data = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 21, 75, 84, 83, 120, 108, 115, 88, 71, 49, 52, 51, 55, 54, 53, 49, 57, 48, 55, 48, 56, 50, 1};
    ChatParser parser;
    ParsedObject parsedObject = parser.parse(data, 0);
    
    shared_ptr<PacketDTO> packet = parsedObject.packet;
    cout<<packet->toString()<<endl;
    cout<<"parsed length = "<<parsedObject.parsedLength<<endl;
}

void test2() {
    std::cout << "chatparsertest test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (chatparsertest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% chatparsertest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (chatparsertest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (chatparsertest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    
    union floatBit
    {
            float f;
            unsigned char b[4];
    };

    floatBit fb;
    fb.b[0]=143;
    fb.b[1]=123;
    fb.b[2]=190;
    fb.b[3]=65;
    
    cout<<"starting"<<endl;
    cout<<fb.f<<endl;
    for (int i=0; i<4; i++) cout<<(int)fb.b[i]<<" "; cout<<endl;
    
    ByteArray data = {60, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 1};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;
    
    cout<<packet->getPacketType()<<endl;
    return (EXIT_SUCCESS);
}

