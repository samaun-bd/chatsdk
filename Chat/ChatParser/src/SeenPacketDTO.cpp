
#include "SeenPacketDTO.h"

namespace imsdk {
SeenPacketDTO::SeenPacketDTO () {}

SeenPacketDTO::SeenPacketDTO(std::string &packetId, long long messageDate, int messageStatus) {
    this->packetID = packetId;
    this->messageDate = messageDate;
    this->messageStatus = messageStatus;
}


SeenPacketDTO::~SeenPacketDTO () { }

/**
* Set the value of packetID
* @param new_var the new value of packetID
*/
void SeenPacketDTO::setPacketID(std::string new_var) {
   packetID = new_var;
}

/**
* Set the value of messageDate
* @param new_var the new value of messageDate
*/
void SeenPacketDTO::setMessageDate(long long new_var) {
   messageDate = new_var;
}

/**
* Get the value of packetID
* @return the value of packetID
*/
std::string SeenPacketDTO::getPacketID()const {
   return packetID;
}

/**
* Get the value of messageDate
* @return the value of messageDate
*/
long long SeenPacketDTO::getMessageDate()const {
   return messageDate;
}

void SeenPacketDTO::setMessageStatus(int messageStatus) {
    this->messageStatus = messageStatus;
}

int SeenPacketDTO::getMessageStatus() const {
    return messageStatus;
}

}

