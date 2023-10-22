/* 
 * File:   Connection.cpp
 * Author: dipal
 * 
 * Created on August 23, 2015, 4:45 PM
 */

#include <memory>
#include <vector>

#include "Connection.h"
#include "PacketReceiver.h"
#include "Logger.h"

namespace imsdk {
ChatConnection::ChatConnection(std::shared_ptr< UDPSocket> socket) {
    udpSocket = socket;
    chatServerStatus = NOT_EXISTS;
}

ChatConnection::~ChatConnection() {
}

void ChatConnection::setRegisterServer(std::string registerServerAddress, int registerServerPort) {
    this->registerServerAddress = registerServerAddress;
    this->registerServerPort = registerServerPort;
    
    this->chatServerAddress = registerServerAddress;
    this->chatServerPort = -1;
    
    this->chatServerStatus = PROCESSING;
}

std::string ChatConnection::getRegisterServerAddress() {
    return registerServerAddress;
}

void ChatConnection::setChatServerPort(int chatServerPort) {
    this->chatServerPort = chatServerPort;
    
    this->chatServerStatus = READY;
}

void ChatConnection::setOfflineServer(std::string offlineServerAddress, int offlineServerPort) {
    this->offlineServerAddress = offlineServerAddress;
    this->offlineServerPort = offlineServerPort;
}

int ChatConnection::sendToRegisterServer(std::shared_ptr< ByteArray> &registerPacket) {
    int ret=0;
    
    if (udpSocket) {
        ret = udpSocket->sendTo(registerPacket->getDataPtr(), (int) registerPacket->size(), this->registerServerAddress, this->registerServerPort);
    }

    return ret;
}

int ChatConnection::sendToChatServer(std::shared_ptr< ByteArray> &chatPacket) {
    int ret=0;
    
    if (udpSocket) {
        ret = udpSocket->sendTo(chatPacket->getDataPtr(), (int) chatPacket->size(), this->chatServerAddress, this->chatServerPort);
    }

    return ret;
}

int ChatConnection::sendToOfflineServer(std::shared_ptr< ByteArray> &offlinePacket) {
    int ret=0;
    
    Log("SOCK", "Offline sending "<<this->offlineServerAddress<<":"<<this->offlineServerPort);
    if (udpSocket) {
        ret = udpSocket->sendTo(offlinePacket->getDataPtr(), (int) offlinePacket->size(), this->offlineServerAddress, this->offlineServerPort);
    }

    return ret;
}

ChatConnection::ChatServerStatus ChatConnection::getChatServerStatus()
{
    return chatServerStatus;
}

int ChatConnection::getRegisterServerPort(){
    return registerServerPort;
}

int ChatConnection::getChatServerPort(){
    return chatServerPort;
}

}
