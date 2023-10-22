/* 
 * File:   SeenPacketDTO.h
 * Author: root
 *
 * Created on December 2, 2015, 4:20 PM
 */

#ifndef SEENPACKETDTO_H
#define	SEENPACKETDTO_H

#include <string>
#include <vector>


namespace imsdk {
class SeenPacketDTO{
public:
    
    SeenPacketDTO();
    SeenPacketDTO(std::string &packetId, long long messageDate, int messageStatus);
    ~SeenPacketDTO();
    void setPacketID(std::string new_var);
    void setMessageDate(long long new_var);
    std::string getPacketID()const;
    long long getMessageDate()const;
    void setMessageStatus(int messageStatus);
    int getMessageStatus() const;
    
private:
    std::string packetID;
    long long messageDate{0};
    int messageStatus{0};
};
}
#endif	/* SEENPACKETDTO_H */

