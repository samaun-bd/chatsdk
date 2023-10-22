/* 
 * File:   ChatParser.cpp
 * Author: dipal
 * 
 * Created on July 12, 2015, 2:29 PM
 */

#include "ChatParser.h"
#include "PacketTemplate.h"
#include "PacketDTO.h"
#include "SDKMessageDTO.h"
#include "ParserTypes.h"

#include <iostream>
#include <unordered_map>


namespace imsdk {
ChatParser::ChatParser() {
    packetTemplate = std::make_shared<PacketTemplate>();
}

ParsedObject ChatParser::parse (ByteArray &data, int startIndex)
{
//    cout<<"Parsing inside of libchatparser. startindex:"<<startIndex<<endl;
    if (data.size()<=0) 
    {
        return {NULL, 0};
    }
    
    std::shared_ptr<PacketDTO> packet = std::make_shared<PacketDTO>();
    
    size_t packetTypeToSet = data[startIndex];
    
    if(data[startIndex] == 0){
        startIndex++;
        packetTypeToSet = data[startIndex]+1000;
    }
    else if(data[startIndex] == 121){
        startIndex++;
        packetTypeToSet = data[startIndex] + 2000;
    }
    else if(data[startIndex] == 122){
        startIndex++;
        packetTypeToSet = data[startIndex] + 3000;
    }
    else if (data[startIndex] == 123){
        startIndex++;
        packetTypeToSet = data[startIndex] + 4000;
    }
    //cout<<"PARSING PT:"<<packetTypeToSet<<endl;
//    cout<<"packet type to set : "<<packetTypeToSet<<endl;
    std::vector<int> format = packetTemplate->getFormat(packetTypeToSet);
    
    if (format.size()<=0)
    {
//        cout<<"hello world: "<<-1<<endl;
        return {NULL, 0};
    }
    packet->setPacketType(packetTypeToSet);
    
    //cout<<"packet type "<<packet->getPacketType()<<endl;
    int i = startIndex + 1;

    for (std::vector<int>::size_type j = 1; j < format.size(); j++)
    {
        if (i>=data.size()) 
        {
            //cout<<2<<endl;
            if (format[j] == OPTIONAL_FIELD)
            {
                return {packet, i-startIndex};;
            }
            return {NULL, 0};
        }
        //cout<<"=>> "<<i+1<<endl;
        switch(format[j]) {
            case OPTIONAL_FIELD:
            {
                break;
            }
            case USER_IDENTITY:
            {
                packet->setUserIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                i+=LEN_USER_IDENTITY;
                //cout<<"userid "<<packet->getUserIdentity()<<endl;
                break;
            }   
            case FRIEND_IDENTITY:
            {
                packet->setFriendIdentity(data.getLongLong(i, LEN_FRIEND_IDENTITY));
                i+=LEN_FRIEND_IDENTITY;
                //cout<<"friend "<<packet->getFriendIdentity()<<endl;
                break;
            }   
            case ORIGINAL_USER_IDENTITY:
            {
                packet->setOriginalUserId(data.getLongLong(i, LEN_ORIGINAL_USER_IDENTITY));
                i+=LEN_ORIGINAL_USER_IDENTITY;
                //cout<<"friend "<<packet->getFriendIdentity()<<endl;
                break;
            }
            case RING_ID:
            {
                packet->setRingId(data.getLongLong(i, LEN_RING_ID));
                i+=LEN_RING_ID;
//                cout<<"ringId "<<packet->getRingId()<<endl;
                break;
            }
            case PUBLISHER_ID:
            {
                packet->setPublisherId(data.getLongLong(i, LEN_PUBLISHER_ID));
                i+=LEN_PUBLISHER_ID;
                break;
            }
            
            case ORIGINAL_PACKET_TYPE:
            {
                packet->setOriginalPacketType(data.getInt(i, LEN_PACKET_TYPE));
                i+=LEN_PACKET_TYPE;
                break;
            }
            case RECEPIENT_IDENTITY:
            {
                packet->setRecipientId(data.getLongLong(i, LEN_RECEPIENT_IDENTITY));
                i+=LEN_RECEPIENT_IDENTITY;
                //cout<<"friend "<<packet->getFriendIdentity()<<endl;
                break;
            }
            case PACKETID_LENGTH:
            {
                int packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                i+=LEN_PACKETID_LENGTH;
                
                packet->setPacketID(data.getString(i, packetIdLength));
                i+=packetIdLength;
                
//                cout<<"packetid "<<packet->getPacketID()<<endl;
                
                //skip dummy field
                j++;
                break;
            }
            case PIVOTID_LENGTH:
            {
                int pivotIdLength = data.getInt(i, LEN_PIVOTID_LENGTH);
                i += LEN_PIVOTID_LENGTH;

                packet->setPivotID(data.getString(i, pivotIdLength));
                i += pivotIdLength;

                //skip dummy field
                j++;
                break;
            }
            case AUTH_SESSION_ID_LENGTH:
            {
                int authSessionIdLength = data.getInt(i, LEN_AUTH_SESSION_ID_LENGTH);
                i += LEN_AUTH_SESSION_ID_LENGTH;

                packet->setAuthSessionID(data.getString(i, authSessionIdLength));
                i += authSessionIdLength;

                //skip dummy field
                j++;
                break;
            }
            case ORIGINAL_PACKETID_LENGTH:
            {
                int originalPacketIdLength = data.getInt(i, LEN_ORIGINAL_PACKETID_LENGTH);
                i+=LEN_ORIGINAL_PACKETID_LENGTH;
                
                packet->setOriginalPacketID(data.getString(i, originalPacketIdLength));
                i+=originalPacketIdLength;
                
                j++;
                break;
            }
            case PLATFORM:
            {
                packet->setDevice(data.getInt(i, LEN_PLATFORM));
                i+=LEN_PLATFORM;
                break;
            }
            case FRIEND_PLATFORM:
            {
                packet->setFriendDevice(data.getInt(i, LEN_FRIEND_PLATFORM));
                i+=LEN_FRIEND_PLATFORM;
                break;
            }
            case CHAT_BINDING_PORT:
            {
                packet->setChatBindingPort(data.getInt(i, LEN_CHAT_BINDING_PORT));
                i+=LEN_CHAT_BINDING_PORT;
                break;
            }   
            case SERVER_DATE:
            {
                packet->setServerDate(data.getLongLong(i, LEN_SERVER_DATE));
                i+=LEN_SERVER_DATE;
                break;
            }   
            case GROUPID:
            {
                packet->setGroupId(data.getLongLong(i, LEN_GROUPID));
                i+=LEN_GROUPID;
                break;
            }   
            case LEAVE_TYPE:
            {
                packet->setGroupLeaveType(data.getInt(i, LEN_LEAVE_TYPE));
                i += LEN_LEAVE_TYPE;
                break;
            }
            case ONLINE_STATUS:
            {
                packet->setOnlineStatus(data.getInt(i, LEN_ONLINE_STATUS));
                i+=LEN_ONLINE_STATUS;
                break;
            }   
            case MESSAGE_TYPE:
            {
                packet->setMessageType(data.getInt(i, LEN_MESSAGE_TYPE));
                i+=LEN_MESSAGE_TYPE;
                break;
            } 
			case TYPE:
			{
				packet->setType(data.getInt(i, LEN_TYPE));
				i += LEN_TYPE;
				break;
			}

			case INFORMATION_TYPE:
			{
				packet->setInformationType(data.getInt(i, LEN_INFORMATION_TYPE));
				i += LEN_INFORMATION_TYPE;
				break;
			}
            case TIMEOUT:
            {
                packet->setTimeout(data.getInt(i, LEN_TIMEOUT));
                i+=LEN_TIMEOUT;
                break;
            }   
            case MESSAGE_LENGTH:
            {
                //cout<<"handling message length"<<endl;
                //cout<<i+1<<endl;
                int messageLength = data.getInt(i, LEN_MESSAGE_LENGTH);
                i+=LEN_MESSAGE_LENGTH;
                //cout<<i+1<<endl;
                
                //cout<<"messagelength : "<<messageLength<<endl;
                std::string message = data.getString(i, messageLength);
                i+=messageLength;
                
                //cout<<"message :"<<message<<endl;
                packet->setMessage(message);
                
                //skipping dummy field
                j++;
                break;
            }

			case INFORMATION_LENGTH:
			{
				//cout<<"handling message length"<<endl;
				//cout<<i+1<<endl;
				int infoLength = data.getInt(i, LEN_INFORMATION_LENGTH);
				i += LEN_INFORMATION_LENGTH;
				//cout<<i+1<<endl;

				//cout<<"messagelength : "<<messageLength<<endl;
				std::string info = data.getString(i, infoLength);
				i += infoLength;

				//cout<<"message :"<<message<<endl;
				packet->setInformation(info);

				//skipping dummy field
				j++;
				break;
			}

            case MESSAGE_DATE:
            {
                packet->setMessageDate(data.getLongLong(i, LEN_MESSAGE_DATE));
                i+=LEN_MESSAGE_DATE;
                break;
            }

            case LAST_SYNC_TIME:
            {
                packet->setLastSyncTime(data.getLongLong(i, LEN_LAST_SYNC_TIME));
                i += LEN_LAST_SYNC_TIME;
                break;
            }

            case NUMBER_OF_MESSAGES:
            case NUMBER_OF_MESSAGES_2B:
            {
                
                int numberOfMessages = 0;
                if (format[j] == NUMBER_OF_MESSAGES)
                {
                    numberOfMessages = data.getInt(i, LEN_NUMBER_OF_MESSAGES);
                    i+=LEN_NUMBER_OF_MESSAGES;
                }
                else 
                {
                    numberOfMessages = data.getInt(i, LEN_NUMBER_OF_MESSAGES_2B);
                    i+=LEN_NUMBER_OF_MESSAGES_2B;
                }
                
//                cout<<"got number of message :"<<numberOfMessages<<endl;
                //packet->setNumberOfMessage(numberOfMessages);
                
                
                j++;
                int innerFormatType = format[j];
                for (int k=0; k<numberOfMessages; k++)
                {
                    //preserve actual type
                    byte actualPacketType = data[i];
                    
                    //set format for inner type
                    data[i] = (byte) innerFormatType;
                    
                    ParsedObject parsedObject = parse(data, i);
//                    cout<<"parsed lenght "<<parsedObject.parsedLength<<endl;
                    if (parsedObject.parsedLength<=0 || parsedObject.packet==NULL) 
                    {
//                        cout<<3<<endl;
                        return {NULL, 0};
                    }
                     
                    //restore actual type into packet
                    parsedObject.packet->setPacketType(actualPacketType);
                    
                    packet->appendMessage(parsedObject.packet);
//                        cout<<packet->getMessageList().back()->toString()<<endl;

                    i+=parsedObject.parsedLength;
                }
                
                break;
            }
            case TOTAL_NUMBER_OF_PACKETS:
            {
                packet->setNumberOfMessage(data.getInt(i, LEN_TOTAL_NUMBER_OF_PACKETS));
                i+=LEN_TOTAL_NUMBER_OF_PACKETS;
                break;
            }   
            case SEQUENCE_NUMBER:
            {
                packet->setSequenceNumber(data.getInt(i, LEN_SEQUENCE_NUMBER));
                i+=LEN_SEQUENCE_NUMBER;
                break;
            }   
            case NUMBER_OF_PACKETS:
            {
                int numberOfPacketIds = data.getInt(i, LEN_NUMBER_OF_PACKETS);
                i+=LEN_NUMBER_OF_PACKETS;
                
                int packetIdLength;
                for (int k=0; k<numberOfPacketIds; k++)
                {
                    packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                    i+=LEN_PACKETID_LENGTH;
                    
                    packet->appendPacketID(data.getString(i, packetIdLength));
                    i+=packetIdLength;
                }
                break;
            }   
            case FULL_NAME_LENGTH:
            {
                int fullNameLength = data.getInt(i, LEN_FULL_NAME_LENGTH);
                i+=LEN_FULL_NAME_LENGTH;
                
                packet->setFullName(data.getString(i, fullNameLength));
                i+=fullNameLength;
                
                //skip dummy
                j++;
                break;
            }   
            case NUMBER_OF_MEMBERS_DTO:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS_DTO);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_MEMBERS_DTO;
                
                for (int k=0; k<numberOfMembers; k++)
                {
                    MemberDTO member;
                    member.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    member.setRingId(data.getLongLong(i, LEN_RING_ID));
                    i+=LEN_RING_ID;
                    
                    int nameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i+=LEN_MEMBER_NAME_LENGTH;
                    
                    member.setFullName(data.getString(i, nameLength));
                    i+=nameLength;
                    
                    member.setStatus(data.getInt(i, LEN_MEMBER_STATUS));
                    i+=LEN_MEMBER_STATUS;
                    
                    member.setAddedBy(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    packet->appendMember(member);
                }                
                break;
            }   
            case NUMBER_OF_MEMBERS_ID_N_S:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS_ID_N_S);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_MEMBERS_ID_N_S;
                
                for (int k=0; k<numberOfMembers; k++)
                {
                    MemberDTO member;
                    member.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    member.setRingId(data.getLongLong(i, LEN_RING_ID));
                    i+=LEN_RING_ID;
                    
                    int nameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i+=LEN_MEMBER_NAME_LENGTH;
                    
                    member.setFullName(data.getString(i, nameLength));
                    i+=nameLength;
                    
                    member.setStatus(data.getInt(i, LEN_MEMBER_STATUS));
                    i+=LEN_MEMBER_STATUS;
                    
                    packet->appendMember(member);
                }
                break;
            }
            case NUMBER_OF_SEEN_PACKET:
            {
                int numberOfPacket = data.getInt(i, LEN_NUMBER_OF_SEEN_PACKET);
                i+=LEN_NUMBER_OF_SEEN_PACKET;
                
                int packetIdLength;
                for (int k=0; k<numberOfPacket; k++)
                {
                    SeenPacketDTO seenPacket;
                    
                    packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                    i+=LEN_PACKETID_LENGTH;

                    seenPacket.setPacketID(data.getString(i, packetIdLength));
                    i+=packetIdLength;
                    
                    seenPacket.setMessageDate(data.getLongLong(i, LEN_MESSAGE_DATE));
                    i+=LEN_MESSAGE_DATE;
                    
                    seenPacket.setMessageStatus(data.getInt(i, LEN_MESSAGE_STATUS));
                    i+=LEN_MESSAGE_STATUS;
                    
                    packet->appendSeenMessage(seenPacket);
                }
                break;
            }
            case NUMBER_OF_MEMBERS_ID_S:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS_ID_S);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_MEMBERS_ID_S;
                
                for (int k=0; k<numberOfMembers; k++)
                {
                    MemberDTO member;
                    member.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    member.setStatus(data.getInt(i, LEN_MEMBER_STATUS));
                    i+=LEN_MEMBER_STATUS;
                    
                    packet->appendMember(member);
                }
                break;
            }
            case NUMBER_OF_MEMBERS_ID:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS_ID);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_MEMBERS_ID;
                
                for (int k=0; k<numberOfMembers; k++)
                {
                    MemberDTO member;
                    member.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    packet->appendMember(member);
                }
                break;
            }
            case NUMBER_OF_MEMBERS_ID_T:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS_ID_T);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_MEMBERS_ID_T;
                
                for (int k=0; k<numberOfMembers; k++)
                {
                    MemberDTO member;
                    member.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    member.setSeenTime(data.getLongLong(i, LEN_MESSAGE_DATE));
                    i+=LEN_MESSAGE_DATE;
                    
                    packet->appendMember(member);
                }
                break;
            }
            case FRIEND_ONLINE_STATUS:
            {
                packet->setOnlineStatus(data.getInt(i, LEN_ONLINE_STATUS));
                i+=LEN_ONLINE_STATUS;
                break;
            }   
            case FRIEND_APP_TYPE:
            {
                packet->setAppType(data.getInt(i, LEN_FRIEND_APP_TYPE));
                i+=LEN_FRIEND_APP_TYPE;
                break;
            }   
            case FRIEND_DEVICE_TOKEN_LENGTH:
            {
                int deviceTokenLength = data.getInt(i, LEN_FRIEND_DEVICE_TOKEN_LENGTH);
                i+=LEN_FRIEND_DEVICE_TOKEN_LENGTH;
                
                packet->setFriendDeviceToken(data.getString(i, deviceTokenLength));
                i+=deviceTokenLength;
                
                //skip dummy
                j++;
                break;
            }   
            case FILE_TOTAL_CHUNK:
            {
                packet->setFileTotalChunk(data.getInt(i, LEN_FILE_TOTAL_CHUNK));
                i+=LEN_FILE_TOTAL_CHUNK;
                break;
            }
            case FILE_CHUNK_LIST_LENGTH:
            {
                int numberOfChunk = data.getInt(i, LEN_FILE_CHUNK_LIST_LENGTH);
                i+=LEN_FILE_CHUNK_LIST_LENGTH;
                
                std::vector<std::pair<int,int> > fileChunks;
                for (int k=0; k<numberOfChunk; k++)
                {
                    int type = data.getInt(i, LEN_FILE_CHUNK_TYPE);
                    i+=LEN_FILE_CHUNK_TYPE;
                    
                    int from = data.getInt(i, LEN_FILE_CHUNK_CURRENT_INDEX);
                    i+=LEN_FILE_CHUNK_CURRENT_INDEX;
                    
                    int to = from;
                    if (type==1)
                    {
                        to = data.getInt(i, LEN_FILE_CHUNK_CURRENT_INDEX);
                        i+=LEN_FILE_CHUNK_CURRENT_INDEX;
                    }
                    fileChunks.push_back({from, to});
                    
                }
                packet->setFileChunkList(fileChunks);
                break;
            }
            case FILE_CHUNK_CURRENT_INDEX:
            {
                packet->setFileChunkCurrentIndex(data.getInt(i, LEN_FILE_CHUNK_CURRENT_INDEX));
                i+=LEN_FILE_CHUNK_CURRENT_INDEX;
                break;
            }
            case FILE_CONTENT_LENGTH:
            {
                int contentLength = data.getInt(i, LEN_FILE_CONTENT_LENGTH);
                i+=LEN_FILE_CONTENT_LENGTH;
                
                packet->setFileContent(data.getString(i, contentLength));
                i+=contentLength;
                
                //skip dummy
                j++;
                break;
            }
            case IS_ADD_TO_BLOCK:
            {
                packet->setIsAddToBlock((bool) data.getInt(i, LEN_IS_ADD_TO_BLOCK));
                i+=LEN_IS_ADD_TO_BLOCK;
                break;
            }
            case GROUP_NAME_LENGTH:
            {
                int nameLenght = data.getInt(i, LEN_GROUP_NAME_LENGTH);
                i+=LEN_GROUP_NAME_LENGTH;
                
                packet->setGroupName(data.getString(i, nameLenght));
                i+=nameLenght;
                
                //skip dummy
                j++;
                break;
            }
            case GROUP_URL_LENGTH:
            {
                int urlLength = data.getInt(i, LEN_GROUP_URL_LENGTH);
                i+=LEN_GROUP_URL_LENGTH;
                
                packet->setGroupUrl(data.getString(i, urlLength));
                i+=urlLength;
                
                //skip dummy
                j++;
                break;
            }
            case ONLINE_MOOD:
            {
                packet->setOnlineMood(data.getInt(i, LEN_ONLINE_MOOD));
                i+=LEN_ONLINE_MOOD;
                break;
            }
            case FILE_TRANSFER_PORT:
            {
                packet->setFileTransferPort(data.getInt(i, LEN_FILE_TRANSFER_PORT));
                i+=LEN_FILE_TRANSFER_PORT;
                break;
            }
            case FILE_ID:
            {
                packet->setFileIdentity(data.getLongLong(i, LEN_FILE_ID));
                i+=LEN_FILE_ID;
                break;
            }
            case FILE_ACCEPT_REJECT:
            {
                packet->setFileAcceptReject((bool) data.getInt(i, LEN_FILE_ACCEPT_REJECT));
                i+=LEN_FILE_ACCEPT_REJECT;
                break;
            }
            case FILE_OFFSET:
            {
                packet->setFileOffset(data.getLongLong(i, LEN_FILE_OFFSET));
                i+=LEN_FILE_OFFSET;
                break;
            }
            case IS_SECRET_VISIBLE:
            {
                packet->setIsSecretVisible((bool)data.getInt(i, LEN_IS_SECRET_VISIBLE));
                i+=LEN_IS_SECRET_VISIBLE;
                break;
            }
            case MESSAGE_STATUS:
            {
                packet->setMessageStatus(data.getInt(i, LEN_MEMBER_STATUS));
                i+=LEN_MEMBER_STATUS;
                break;
            }
            case BLOCK_UNBLOCK_DATE:
            {
                packet->setBlockUnblockDate(data.getLongLong(i, LEN_BLOCK_UNBLOCK_DATE));
                i+=LEN_BLOCK_UNBLOCK_DATE;
                break;
            }
            case DATA_BYTES:
            {
                std::shared_ptr<ByteArray> dataBytes = std::make_shared<ByteArray>(data.getDataPtr()+i,data.size()-i);
                packet->setDataBytes(dataBytes);
                break;
            }
            case GROUP_UPDATE_DATE:
            {
                packet->setGroupUpdateDate(data.getLongLong(i, LEN_GROUP_UPDATE_DATE));
                i+= LEN_GROUP_UPDATE_DATE;
                break;
            }
            case UP_DOWN:
            {
                packet->setUpDownStatus(data.getInt(i, LEN_UP_DOWN));
                i+=LEN_UP_DOWN;
                break;
            }
            case LIMIT:
            {
                packet->setLimit(data.getInt(i, LEN_LIMIT));
                i+=LEN_LIMIT;
                break;
            }
            case NUMBER_OF_ACTIVITY:
            {
                int numberOfActivity = data.getInt(i, LEN_NUMBER_OF_ACTIVITY);
                i+=LEN_NUMBER_OF_ACTIVITY;
                
                for (int j=0; j<numberOfActivity; j++)
                {
                    GroupActivityDTO groupActivity;
                    groupActivity.setActivityType(data.getInt(i, LEN_ACTIVITY_TYPE));
                    i+=LEN_ACTIVITY_TYPE;
                    
                    groupActivity.setMemberIdentity(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    int groupNameOrUrlStringLength = data.getInt(i, LEN_GROUP_NAME_URL_LENGTH);
                    i+=LEN_GROUP_NAME_URL_LENGTH;
                    
                    groupActivity.setGroupNameOrUrlString(data.getString(i, groupNameOrUrlStringLength));
                    i+=groupNameOrUrlStringLength;
                    
                    groupActivity.setMemberType(data.getInt(i, LEN_MEMBER_STATUS));
                    i+=LEN_MEMBER_STATUS;
                    
                    groupActivity.setChangedByUserId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    groupActivity.setUpdateTime(data.getLongLong(i, LEN_GROUP_UPDATE_DATE));
                    i+=LEN_GROUP_UPDATE_DATE;
                    
                    packet->appendGroupAcitivity(groupActivity);
                }
                break;
            }
            case ACTIVITY_TYPE:
            {
                int activityType = data.getInt(i, LEN_ACTIVITY_TYPE);
                packet->setGroupActivityType(activityType);
                i+=LEN_ACTIVITY_TYPE;
                
                if (activityType == GROUP_NAME_CHANGE) //GROUP_RENAME
                {
                    int groupNameLength = data.getInt(i, LEN_GROUP_NAME_LENGTH);
                    i+=LEN_GROUP_NAME_LENGTH;
                    
                    std::string groupName = data.getString(i, groupNameLength);
                    i+=groupNameLength;
                    
                    packet->setGroupName(groupName);
                }
                else if (activityType == GROUP_URL_CHANGE) //GROUP_URL_CHANGE
                {
                    int groupUrlLength = data.getInt(i, LEN_GROUP_URL_LENGTH);
                    i+=LEN_GROUP_URL_LENGTH;
                    
                    std::string groupUrl = data.getString(i, groupUrlLength);
                    i+=groupUrlLength;
                    
                    packet->setGroupUrl(groupUrl);
                }
                
                break;
            }
            case NUMBER_OF_GROUPS:
            {
                int numberOfGroups = data.getInt(i, LEN_NUMBER_OF_GROUPS);
                i+=LEN_NUMBER_OF_GROUPS;
                
                for (int j=0; j<numberOfGroups; j++)
                {
                    GroupDTO groupDTO;
                    groupDTO.setGroupId(data.getLongLong(i, LEN_GROUPID));
                    i+=LEN_GROUPID;
                    
                    int groupNameLength = data.getInt(i, LEN_GROUP_NAME_LENGTH);
                    i+=LEN_GROUP_NAME_LENGTH;
                    
                    groupDTO.setGroupName(data.getString(i, groupNameLength));
                    i+=groupNameLength;
                    
                    int groupUrlLength = data.getInt(i, LEN_GROUP_URL_LENGTH);
                    i+=LEN_GROUP_URL_LENGTH;
                    
                    groupDTO.setGroupUrl(data.getString(i, groupUrlLength));
                    i+=groupUrlLength;
                    
                    groupDTO.setCreatorId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                    
                    groupDTO.setNumberOfMembers(data.getInt(i, LEN_NUMBER_OF_MEMBERS));
                    i+=LEN_NUMBER_OF_MEMBERS;
                    
                    packet->appendGroupDTO(groupDTO);
                }
                break;
            }
            case NUMBER_OF_MEMBERS:
            {
                packet->setNumberOfMembers(data.getInt(i, LEN_NUMBER_OF_MEMBERS));
                i+=LEN_NUMBER_OF_MEMBERS;
                break;
            }
            case NUMBER_OF_PACKETS_D_S:
            {
                int numberOfStatus = data.getInt(i, LEN_NUMBER_OF_PACKETS_D_S);
                i+=LEN_NUMBER_OF_PACKETS_D_S;
                
                for (int j=0; j<numberOfStatus; j++)
                {
                    FriendMessageStatusDTO friendMessageStatusDTO;
                    
                    int packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                    i+=LEN_PACKETID_LENGTH;
                    
                    friendMessageStatusDTO.setPacketId(data.getString(i, packetIdLength));
                    i+=packetIdLength;
                    
                    friendMessageStatusDTO.setUpdateDate(data.getLongLong(i, LEN_MESSAGE_DATE));
                    i+=LEN_MESSAGE_DATE;
                    
                    friendMessageStatusDTO.setMessageStatus(data.getInt(i, LEN_MESSAGE_STATUS));
                    i+=LEN_MESSAGE_STATUS;
                    
                    packet->appendFriendMessageStatusDTO(friendMessageStatusDTO);
                }
                break;
            }
            case APP_VERSION:
            {
                packet->setAppVersion(data.getInt(i, LEN_APP_VERSION));
                i+=LEN_APP_VERSION;
                break;
            }
            
			case PROFILE_TYPE:
			{
				packet->setProfileType(data.getInt(i, LEN_PROFILE_TYPE));
				i += LEN_PROFILE_TYPE;
				break;
			}

            case FRIEND_PROFILE_TYPE:
            {
                packet->setFriendProfileType(data.getInt(i, LEN_FRIEND_PROFILE_TYPE));
                i += LEN_FRIEND_PROFILE_TYPE;
                break;
            }

            case MESSAGE_DELETE_TYPE:
            {
                packet->setMessageDeleteType(data.getInt(i, LEN_MESSAGE_DELETE_TYPE));
                i += LEN_MESSAGE_DELETE_TYPE;
                break;
            }

			case PAGE_OWNER_IDENTITY:
			{
				packet->setPageOwnerId(data.getInt(i, LEN_PAGE_OWNER_IDENTITY));
				i += LEN_PAGE_OWNER_IDENTITY;
				break;
			}

            //Public Room Chat
            
            case ROOM_IDENTITY_LENGTH:
            {
                int roomIdentityLength = data.getInt(i, LEN_ROOM_IDENTITY_LENGTH);
                i += LEN_ROOM_IDENTITY_LENGTH;
                
                std::string roomId = data.getString(i, roomIdentityLength);
                packet->setRoomId(roomId);
                i += roomIdentityLength;
                
                j++;
                break;
            }
            
            case ROOM_FULL_NAME_LENGTH:
            {
                int roomFullNameLength = data.getInt(i, LEN_ROOM_FULL_NAME_LENGTH);
                i += LEN_ROOM_FULL_NAME_LENGTH;
                
                std::string roomFullName = data.getString(i, roomFullNameLength);
                packet->setRoomFullName(roomFullName);
                i += roomFullNameLength;
                
                j++;
                break;
            }
            
            case MEMBER_PROFILE_URL_LENGTH:
            {
                int roomUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                i += LEN_MEMBER_PROFILE_URL_LENGTH;
                
                std::string roomUrl = data.getString(i, roomUrlLength);
                packet->setRoomUrl(roomUrl);
                i += roomUrlLength;
                
                j++;
                break;
            }

            case FRIEND_PROFILE_IAMGE_URL_LENGTH:
            {
                int profileImageUrlLength = data.getInt(i, LEN_FRIEND_PROFILE_IAMGE_URL_LENGTH);
                i += LEN_FRIEND_PROFILE_IAMGE_URL_LENGTH;

                std::string profileImageUrl = data.getString(i, profileImageUrlLength);
                packet->setFriendProfileImageUrl(profileImageUrl);
                i += profileImageUrlLength;

                j++;
                
                break;
            }

            case ACCOUNT_ACTIVATION_STATUS:
            {
                bool startIndex = data.getInt(i, LEN_ACCOUNT_ACTIVATION_STATUS) > 0 ? true : false;
                i += LEN_ACCOUNT_ACTIVATION_STATUS;
                
                packet->setIsActivateUserAccount(startIndex);
                
                break;
            }
            
            case START_INDEX:
            {
                int startIndex = data.getInt(i, LEN_START_INDEX);
                i += LEN_START_INDEX;
                
                packet->setStartIndex(startIndex);
                
                break;
            }
            
            case SEARCH_NAMELENGTH:
            {
                int roomSearchNameLength = data.getInt(i, LEN_SEARCH_NAMELENGTH);
                i += LEN_SEARCH_NAMELENGTH;
                
                std::string roomSearchName = data.getString(i, roomSearchNameLength);
                packet->setRoomSearchName(roomSearchName);
                i += roomSearchNameLength;
                
                j++;
                break;
            }
            
            case NUMBER_OF_ROOM:
            {
                std::vector<RoomDTO> roomList;
                int numberOfRoom = data.getInt(i, LEN_NUMBER_OF_ROOM);
                
                
                
                i += LEN_NUMBER_OF_ROOM;
                
                for(int k=0; k<numberOfRoom; k++){
                    RoomDTO roomDTO;
                    
                    int roomIdLength = data.getInt(i, LEN_ROOM_IDENTITY_LENGTH);
                    i += LEN_ROOM_IDENTITY_LENGTH;
                    std::string roomId = data.getString(i, roomIdLength);
                    i += roomIdLength;
                    roomDTO.setRoomId(roomId);
                    
                    int roomFullNameLength = data.getInt(i, LEN_ROOM_FULL_NAME_LENGTH);
                    i += LEN_ROOM_FULL_NAME_LENGTH;
                    std::string roomFullName = data.getString(i, roomFullNameLength);
                    i += roomFullNameLength;
                    roomDTO.setRoomFullName(roomFullName);
                    
                    int roomPictureUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    std::string roomPictureUrl = data.getString(i, roomPictureUrlLength);
                    i += roomPictureUrlLength;
                    roomDTO.setRoomPictureUrl(roomPictureUrl);
                    
                    roomList.push_back(roomDTO);
                }
                
                packet->setRoomList(roomList);
                
                break;
            }
            
            case NUMBER_OF_ROOM_WITH_HISTORY:
            {
                std::vector<RoomDTO> roomList;
                int numberOfRoom = data.getInt(i, LEN_NUMBER_OF_ROOM);
                
                
                
                i += LEN_NUMBER_OF_ROOM;
                
                for(int k=0; k<numberOfRoom; k++){
                    RoomDTO roomDTO;
                    
                    int roomIdLength = data.getInt(i, LEN_ROOM_IDENTITY_LENGTH);
                    i += LEN_ROOM_IDENTITY_LENGTH;
                    std::string roomId = data.getString(i, roomIdLength);
                    i += roomIdLength;
                    roomDTO.setRoomId(roomId);
                    
                    int roomFullNameLength = data.getInt(i, LEN_ROOM_FULL_NAME_LENGTH);
                    i += LEN_ROOM_FULL_NAME_LENGTH;
                    std::string roomFullName = data.getString(i, roomFullNameLength);
                    i += roomFullNameLength;
                    roomDTO.setRoomFullName(roomFullName);
                    
                    int roomPictureUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    std::string roomPictureUrl = data.getString(i, roomPictureUrlLength);
                    i += roomPictureUrlLength;
                    roomDTO.setRoomPictureUrl(roomPictureUrl);
                    
                    int numberOfRoomMember = data.getInt(i, LEN_NUMBER_OF_ROOM_MEMBER);
                    i += LEN_NUMBER_OF_ROOM_MEMBER;
                    roomDTO.setNumberOfMember(numberOfRoomMember);
                    
                    std::vector<SDKMessageDTO> messageList;
                    int numberOfPublicChatMessages = data.getInt(i, LEN_NUMBER_OF_MESSAGES);
                    i += LEN_NUMBER_OF_MESSAGES;

                    for(int k=0; k<numberOfPublicChatMessages; k++){
                        SDKMessageDTO messageDTO;

                        messageDTO.setSenderId(data.getLongLong(i, LEN_USER_IDENTITY));
                        i += LEN_USER_IDENTITY;

                        int packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                        i += LEN_PACKETID_LENGTH;
                        std::string packetId = data.getString(i, packetIdLength);
                        i += packetIdLength;
                        messageDTO.setPacketId(packetId);

                        messageDTO.setMessageType(data.getInt(i, LEN_MESSAGE_TYPE));
                        i += LEN_MESSAGE_TYPE;
                        
                        int messageLength = data.getInt(i, LEN_MESSAGE_LENGTH);
                        i += LEN_MESSAGE_LENGTH;
                        std::string message = data.getString(i, messageLength);
                        i += messageLength;
                        messageDTO.setMessage(message);

                        messageDTO.setMessageDate(data.getLongLong(i, LEN_MESSAGE_DATE));
                        i += LEN_MESSAGE_DATE;


                        int memberFullNameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                        i += LEN_MEMBER_NAME_LENGTH;
                        std::string memberFullName = data.getString(i, memberFullNameLength);
                        i += memberFullNameLength;
                        messageDTO.setMemberFullName(memberFullName);

                        int memberProfileUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                        i += LEN_MEMBER_PROFILE_URL_LENGTH;
                        std::string memberProfileUrl = data.getString(i, memberProfileUrlLength);
                        i += memberProfileUrlLength;
                        messageDTO.setMemberProfileUrl(memberProfileUrl);
                        
                        messageList.push_back(messageDTO);
                    }

                    roomDTO.setRoomMessageList(messageList);
                    
                    roomList.push_back(roomDTO);
                }
                
                packet->setRoomList(roomList);
                
                break;
            }
            
            case SERVER_IP_LENGTH:
            {
                int roomServerIpLength = data.getInt(i, LEN_SERVER_IP_LENGTH);
                i += LEN_SERVER_IP_LENGTH;
                
                std::string roomServerIp = data.getString(i, roomServerIpLength);
                packet->setServerIp(roomServerIp);
                i += roomServerIpLength;
                
                j++;
                break;
            }
            
            case SERVER_REGISTER_PORT:
            {
                int roomServerRegisterPort = data.getInt(i, LEN_SERVER_REGISTER_PORT);
                i += LEN_SERVER_REGISTER_PORT;
                
                packet->setServerPort(roomServerRegisterPort);
                
                break;
            }
            
            case NUMBER_OF_PUBLIC_CHAT_MEMBERS:
            {
                std::vector<PublicChatMemberDTO> publicChatMembersList;
                
                int numberOfPublicChatMembers = data.getInt(i, LEN_NUMBER_OF_MEMBERS);
                i += LEN_NUMBER_OF_MEMBERS;
                
                for(int k=0; k<numberOfPublicChatMembers; k++){
                    PublicChatMemberDTO publicChatMember;
                    
                    publicChatMember.setMemberId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    publicChatMember.setFakeId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    publicChatMember.setRingId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    int fullNameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i += LEN_MEMBER_NAME_LENGTH;
                    
                    publicChatMember.setFullName(data.getString(i, fullNameLength));
                    i += fullNameLength;
                    
                    int profileUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    
                    publicChatMember.setProfileUrl(data.getString(i, profileUrlLength));
                    i += profileUrlLength;
                    
                    publicChatMember.setAddedTime(data.getLongLong(i, LEN_MEMBER_ADDED_TIME));
                    i += LEN_MEMBER_ADDED_TIME;
                    
                    publicChatMembersList.push_back(publicChatMember);
                }
                
                packet->setPublicChatMemberList(publicChatMembersList);
                
                break;
            }
            case NUMBER_OF_PUBLIC_CHAT_LIKERS_ID:
            {
                std::vector<PublicChatMemberDTO> publicChatMembersList;
                
                int numberOfPublicChatMembers = data.getInt(i, LEN_NUMBER_OF_PUBLIC_CHAT_LIKERS_ID);
                i += LEN_NUMBER_OF_PUBLIC_CHAT_LIKERS_ID;
                
                for(int k=0; k<numberOfPublicChatMembers; k++){
                    PublicChatMemberDTO publicChatMember;
                    
                    publicChatMember.setMemberId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    publicChatMember.setRingId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                                        
                    int fullNameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i += LEN_MEMBER_NAME_LENGTH;
                    
                    publicChatMember.setFullName(data.getString(i, fullNameLength));
                    i += fullNameLength;
                    
                    int profileUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    
                    publicChatMember.setProfileUrl(data.getString(i, profileUrlLength));
                    i += profileUrlLength;
                    
                    publicChatMembersList.push_back(publicChatMember);
                }
                
                packet->setPublicChatMemberList(publicChatMembersList);
                
                break;
            }
            case NUMBER_OF_PUBLIC_ROOM_CATEGORY:
            {
                int numberOfPublicRoomCategory = data.getInt(i, LEN_NUMBER_OF_PUBLIC_ROOM_CATEGORY);
                packet->setNumberOfPublicRoomCategory(numberOfPublicRoomCategory);
                i+=LEN_NUMBER_OF_PUBLIC_ROOM_CATEGORY;
                
                std::vector<std::string> publicRoomCategoryList;
                for(int k=0; k<numberOfPublicRoomCategory; k++){
                    int publicRoomCategoryLength = data.getInt(i, LEN_PUBLIC_ROOM_CATEGORY_LENGHT);
                    i+=LEN_PUBLIC_ROOM_CATEGORY_LENGHT;
                    publicRoomCategoryList.push_back(data.getString(i, publicRoomCategoryLength));
                    i+=publicRoomCategoryLength;
                }
                                
                packet->setPublicRoomCategoryList(publicRoomCategoryList);
                
                break;
            }
            
            case NUMBER_OF_PUBLIC_CHAT_MESSAGES:
            {
                std::vector<SDKMessageDTO> messageList;
                int numberOfPublicChatMessages = data.getInt(i, LEN_NUMBER_OF_MESSAGES);
                i += LEN_NUMBER_OF_MESSAGES;
                
                for(int k=0; k<numberOfPublicChatMessages; k++){
                    SDKMessageDTO messageDTO;
                    
                    messageDTO.setSenderId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    int packetIdLength = data.getInt(i, LEN_PACKETID_LENGTH);
                    i += LEN_PACKETID_LENGTH;
                    std::string packetId = data.getString(i, packetIdLength);
                    i += packetIdLength;
                    messageDTO.setPacketId(packetId);
                    
                    messageDTO.setMessageType(data.getInt(i, LEN_MESSAGE_TYPE));
                    i += LEN_MESSAGE_TYPE;
                                        
                    int messageLength = data.getInt(i, LEN_MESSAGE_LENGTH);
                    i += LEN_MESSAGE_LENGTH;
                    std::string message = data.getString(i, messageLength);
                    i += messageLength;
                    messageDTO.setMessage(message);
                    
                    messageDTO.setMessageDate(data.getLongLong(i, LEN_MESSAGE_DATE));
                    i += LEN_MESSAGE_DATE;
                    
                    
                    int memberFullNameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i += LEN_MEMBER_NAME_LENGTH;
                    std::string memberFullName = data.getString(i, memberFullNameLength);
                    i += memberFullNameLength;
                    messageDTO.setMemberFullName(memberFullName);
                    
                    int memberProfileUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    std::string memberProfileUrl = data.getString(i, memberProfileUrlLength);
                    i += memberProfileUrlLength;
                    messageDTO.setMemberProfileUrl(memberProfileUrl);
                    
                    messageList.push_back(messageDTO);
                }
                
                packet->setChatMessageList(messageList);
                
                break;
            }
            
            case MONTH: 
            {
                int month = data.getInt(i, LEN_MONTH);
                i+=LEN_MONTH;
                
                packet->setMonth(month);
                
                break;
            }
            
            case YEAR: 
            {
                int year = data.getInt(i, LEN_YEAR);
                i+=LEN_YEAR;
                
                packet->setYear(year);
                
                break;
            }
            
            case PAGING_STATE_LENGTH:
            {
                int pagingStateLength = data.getInt(i, LEN_PAGING_STATE_LENGHT);
                i += LEN_PAGING_STATE_LENGHT;
                
                std::string pagingState = data.getString(i, pagingStateLength);
                packet->setPagingState(pagingState);
                i += pagingStateLength;
                
                j++;
                break;
            }
            
            case NUMBER_OF_PUBLIC_CHAT_MEMBERS_C:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_PUBLIC_CHAT_MEMBERS_C);
                i+=LEN_NUMBER_OF_PUBLIC_CHAT_MEMBERS_C;
                
                packet->setNumberOfMembers(numberOfMembers);
                break;
            }
            
            case NUMBER_OF_SHADOW_INFO_ID:
            {
                std::vector<PublicChatMemberDTO> publicChatMembersList;
                
                int numberOfPublicChatMembers = data.getInt(i, LEN_NUMBER_OF_SHADOW_INFO_ID);
                i += LEN_NUMBER_OF_SHADOW_INFO_ID;
                
                for(int k=0; k<numberOfPublicChatMembers; k++){
                    PublicChatMemberDTO publicChatMember;
                    
                    int roomIdLength = data.getInt(i, LEN_ROOM_IDENTITY_LENGTH);
                    i += LEN_ROOM_IDENTITY_LENGTH;
                    
                    publicChatMember.setRoomId(data.getString(i, roomIdLength));
                    i += roomIdLength;
                    
                    publicChatMember.setMemberId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    publicChatMember.setFakeId(data.getLongLong(i, LEN_USER_IDENTITY));
                    i += LEN_USER_IDENTITY;
                    
                    int fullNameLength = data.getInt(i, LEN_MEMBER_NAME_LENGTH);
                    i += LEN_MEMBER_NAME_LENGTH;
                    
                    publicChatMember.setFullName(data.getString(i, fullNameLength));
                    i += fullNameLength;
                    
                    int profileUrlLength = data.getInt(i, LEN_MEMBER_PROFILE_URL_LENGTH);
                    i += LEN_MEMBER_PROFILE_URL_LENGTH;
                    
                    publicChatMember.setProfileUrl(data.getString(i, profileUrlLength));
                    i += profileUrlLength;
                    
                    publicChatMembersList.push_back(publicChatMember);
                }
                
                packet->setPublicChatMemberList(publicChatMembersList);
                
                break;
            }
            
            case NUMBER_OF_SHADOW_ID:
            {
                int numberOfMembers = data.getInt(i, LEN_NUMBER_OF_SHADOW_ID);
                packet->setNumberOfMembers(numberOfMembers);
                i+=LEN_NUMBER_OF_SHADOW_ID;
                
                std::vector<UserIdentity> shadowIdList;
                for (int k=0; k<numberOfMembers; k++)
                {
                    
                    shadowIdList.push_back(data.getLongLong(i, LEN_USER_IDENTITY));
                    i+=LEN_USER_IDENTITY;
                }
                packet->setShadowIdList(shadowIdList);
                break;
            }
            
            case PUBLIC_CHAT_LIKE_COUNT:
            {
                int publicChatLikeCount = data.getInt(i, LEN_PUBLIC_CHAT_LIKE_COUNT);
                packet->setPublicChatLikeCount(publicChatLikeCount);
                i+=LEN_PUBLIC_CHAT_LIKE_COUNT;
                break;
            }
            
            case PUBLIC_CHAT_ILIKE:
            {
                bool publicChatILike = (bool) data.getInt(i, LEN_PUBLIC_CHAT_ILIKE);
                packet->setPublicChatILike(publicChatILike);
                i+=LEN_PUBLIC_CHAT_ILIKE;
                break;
            }
            
            case PUBLIC_CHAT_IREPORT:
            {
                bool publicChatIReport = (bool) data.getInt(i, LEN_PUBLIC_CHAT_IREPORT);
                packet->setPublicChatIReport(publicChatIReport);
                i+=LEN_PUBLIC_CHAT_IREPORT;
                break;
            }
            
            case IOS_VOIP_PUSH:
            {
                packet->setIosVoipPush(data.getInt(i, LEN_IOS_VOIP_PUSH));
                i+=LEN_IOS_VOIP_PUSH;
                break;
            }
            
            case CONVERSATION_TYPE:
            {
                packet->setConversationType(data.getInt(i, LEN_CONVERSATION_TYPE));
                i+=LEN_CONVERSATION_TYPE;
                break;
            }
            
            case FRIEND_GROUP_ID:
            {
                packet->setFriendOrGroupId(data.getLongLong(i, LEN_FRIEND_GROUP_ID));
                i+=LEN_FRIEND_GROUP_ID;
                break;
            }
            
            case UNREAD_COUNT:
            {
                packet->setUnreadCount(data.getInt(i, LEN_UNREAD_COUNT));
                i+=LEN_UNREAD_COUNT;
                break;
            }
            
            case FILE_DOWNLOAD_ID_LENGTH:
            {
                int fileDownloadIdLength = data.getInt(i, LEN_FILE_DOWNLOAD_ID_LENGTH);
                i+=LEN_FILE_DOWNLOAD_ID_LENGTH;
                
                packet->setFileDownloadId(data.getString(i, fileDownloadIdLength));
                i+=fileDownloadIdLength;
                
                j++;
                break;
            }
            
            case FILE_CHUNK_COUNT:
            {
                packet->setFileChunkCount(data.getInt(i, LEN_FILE_CHUNK_COUNT));
                i+=LEN_FILE_CHUNK_COUNT;
                break;
            }
            
            case FILE_CHUNK_SIZE:
            {
                packet->setFileChunkSize(data.getInt(i, LEN_FILE_CHUNK_SIZE));
                i+=LEN_FILE_CHUNK_SIZE;
                break;
            }
            
            case FILE_SIZE:
            {
                packet->setFileSize(data.getLongLong(i, LEN_FILE_SIZE));
                i+=LEN_FILE_SIZE;
                break;
            }
            
            case IS_FILE_MANIFEST:
            {
                packet->setFileManifest((bool) data.getInt(i, LEN_IS_FILE_MANIFEST));
                i+=LEN_IS_FILE_MANIFEST;
                break;
            }
            
            case FILE_CHUNK_DOWNLOAD_KEY_LENGTH:
            {
                int fileChunkDownloadKeyLength = data.getInt(i, LEN_FILE_CHUNK_DOWNLOAD_KEY_LENGTH);
                i+=LEN_FILE_CHUNK_DOWNLOAD_KEY_LENGTH;
                
                packet->setFileChunkDownloadKey(data.getString(i, fileChunkDownloadKeyLength));
                i+=fileChunkDownloadKeyLength;
                
                j++;
                break;
            }
            
            case FILE_DOMAIN_TYPE:
            {
                packet->setFileDomainType(data.getInt(i, LEN_FILE_DOMAIN_TYPE));
                i+=LEN_FILE_DOMAIN_TYPE;
                break;
            }

            case FILE_CAPTION_LENGTH:
            {
                int fileCaptionLength = data.getInt(i, LEN_FILE_CAPTION_LENGTH);
                i+=LEN_FILE_CAPTION_LENGTH;

                packet->setCaption(data.getString(i, fileCaptionLength));
                i+=fileCaptionLength;

                j++;
                break;
            }

            case FILE_WIDTH_OR_SIZE:
            {
                packet->setWidthOrFileSize(data.getInt(i, LEN_FILE_WIDTH_OR_SIZE));
                i+=LEN_FILE_WIDTH_OR_SIZE;
                break;
            }

            case FILE_HEIGHT_OR_DURATION:
            {
                packet->setHeightOrDuration(data.getInt(i, LEN_FILE_HEIGHT_OR_DURATION));
                i+=LEN_FILE_HEIGHT_OR_DURATION;
                break;
            }
                
            case DISBURSE_TIME:
            {
                packet->setDisburseTime(data.getLongLong(i, LEN_DISBURSE_TIME));
                i+=LEN_DISBURSE_TIME;
                break;
            }
                
            case EXPIRE_TIME:
            {
                packet->setExpireTime(data.getLongLong(i, LEN_EXPIRE_TIME));
                i+=LEN_EXPIRE_TIME;
                break;
            }

            case NOTICE_LENGTH:
            {
                int noticeLength = data.getInt(i, LEN_NOTICE_LENGTH);
                i+=LEN_NOTICE_LENGTH;
                
                packet->setNotice(data.getString(i, noticeLength));
                i+=noticeLength;
                
                j++;
                break;
            }
                
            case ISO_COUNTRY_LENGTH:
            {
                int isoCountryLength = data.getInt(i, LEN_ISO_COUNTRY_LENGTH);
                i+=LEN_ISO_COUNTRY_LENGTH;
                
                std::string isoCountryString = data.getString(i, isoCountryLength);
                i+=isoCountryLength;
                
                std::vector<std::string> isoCountries = getSplittedString(isoCountryString, ',');
                packet->setIsoList(isoCountries);
                
                j++;
                break;
            }
                
            default:
//                cout<<"report exception and return null"<<endl;
//                cout<<data[i]<<endl;
                return {NULL, 0};
                break;
        }
    }
    
    //TODO: add to template after production upload
    if (packetTypeToSet == GROUP_REGISTER_CONFIRMATION && i<data.size()) {
        packet->setMemberInGroup(data[i]==1);
    }
    
    //cout<<5<<endl;
    //cout<<startIndex<<" "<<i<<endl;
    return {packet, i-startIndex};
}

ParsedObject ChatParser::parseHeader(ByteArray& byteArray)
{
    byte packetType = byteArray[0];

    switch (packetType)
    {
        case OFFLINE_GROUP_UNREAD_MESSAGE:
        {
            byteArray[0] = OFFLINE_GROUP_UNREAD_MESSAGE_HEADER;
            auto parsedObject = parse(byteArray);
            byteArray[0] = packetType;
            parsedObject.packet->setPacketType(packetType);
            return parsedObject;
        }
        case FRIEND_CHAT_MESSAGE:
        {
            byteArray[0] = FRIEND_CHAT_MESSAGE_HEADER;
            auto parsedObject = parse(byteArray);
            byteArray[0] = packetType;
            parsedObject.packet->setPacketType(packetType);
            return parsedObject;
        }
        case OFFLINE_CREATE_GROUP:
        {
            byteArray[0] = OFFLINE_CREATE_GROUP_HEADER;
            auto parsedObject = parse(byteArray);
            byteArray[0] = packetType;
            parsedObject.packet->setPacketType(packetType);
            return parsedObject;
        }
    }
    
    return {nullptr, 0};
}

std::shared_ptr<ByteArray> ChatParser::parse (std::shared_ptr<PacketDTO> &packet)
{
    std::shared_ptr<ByteArray> data = std::make_shared<ByteArray>();
    
    std::vector<int> format = packetTemplate->getFormat(packet->getPacketType());
    //cout<<"new Packet type "<<packet->getPacketType()<<endl;
    
    //Public Room Chat :: Append 0 as first byte 
    int packetTypeToSet = packet->getPacketType();
    if(packet->getPacketType() >= 1000 && packet->getPacketType() <= 1100)
    {
        data->push_back(0);
        packetTypeToSet -= 1000;
    } 
    else if(packet->getPacketType() >= 2000 && packet->getPacketType() <= 2100)
    {
        data->push_back(121);
        packetTypeToSet -= 2000;
    }
    else if(packet->getPacketType() >= 3000 && packet->getPacketType() <= 3100)
    {
        data->push_back(122);
        packetTypeToSet -= 3000;
    }
    else if (packet->getPacketType() >= 4000 && packet->getPacketType() <= 4100)
    {
        data->push_back(123);
        packetTypeToSet -= 4000;
    }
    else if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_ANONYMOUS) 
    {
        packetTypeToSet = FRIEND_CHAT_MESSAGE;
    } 
    else if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT_ANONYMOUS) 
    {
        packetTypeToSet = FRIEND_CHAT_MESSAGE_EDIT;
    } 
    else if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_ANONYMOUS) 
    {
        packetTypeToSet = FRIEND_CHAT_MESSAGE_BROKEN;
    } 
    else if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_EDIT_ANONYMOUS) 
    {
        packetTypeToSet = FRIEND_CHAT_MESSAGE_BROKEN_EDIT;
    } 
    
    data->push_back(packetTypeToSet);
    for (std::vector<int>::size_type i = 1; i < format.size(); i++)
    {
        //cout<<"=>>"<<(int)format[i]<<endl;
        if(format[i] == OPTIONAL_FIELD)
            continue;
        
        switch(format[i])
        {
            case FRIEND_IDENTITY:
            {
                data->appendData(packet->getFriendIdentity(), LEN_FRIEND_IDENTITY);
                break;
            }
            case USER_IDENTITY:
            {
                data->appendData(packet->getUserIdentity(), LEN_USER_IDENTITY);
                break;
            } 
			case PAGE_OWNER_IDENTITY:
			{
				data->appendData(packet->getPageOwnerId(), LEN_PAGE_OWNER_IDENTITY);
				break;
			}
            case ACCOUNT_ACTIVATION_STATUS:
            {
                byte isActivate = packet->getIsActivateUserAccount() ? 1 : 0;
                data->appendData(isActivate, LEN_ACCOUNT_ACTIVATION_STATUS);
                break;
            }
            case RING_ID:
            {
                data->appendData(packet->getRingId(), LEN_RING_ID);
                break;
            }
            case PUBLISHER_ID:
            {
                data->appendData(packet->getPublisherId(), LEN_PUBLISHER_ID);
                break;
            }
            case ORIGINAL_USER_IDENTITY:
            {
                data->appendData(packet->getOriginalUserId(), LEN_ORIGINAL_USER_IDENTITY);
                break;
            }
            case PUBLIC_CHAT_LAST_LIKER_ID:
            {
                data->appendData(packet->getLastLikerId(), LEN_PUBLIC_CHAT_LAST_LIKER_ID);
                break;
            }
            case ORIGINAL_PACKET_TYPE:
            {
                data->appendData(packet->getOriginalPacketType(), LEN_PACKET_TYPE);
                break;
            }
            case RECEPIENT_IDENTITY:
            {
                data->appendData(packet->getRecipientId(), LEN_RECEPIENT_IDENTITY);
                break;
            }   
            case PACKETID_LENGTH:
            {
                int packetIdLength = packet->getPacketID().size();
                data->appendData(packetIdLength, LEN_PACKETID_LENGTH);
                data->appendData(packet->getPacketID(), packetIdLength);
                
                //skip dummy
                i++;
                break;
            }
            case PIVOTID_LENGTH:
            {
                int pivotIdLength = packet->getPivotID().size();
                data->appendData(pivotIdLength, LEN_PIVOTID_LENGTH);
                data->appendData(packet->getPivotID(), pivotIdLength);

                //skip dummy
                i++;
                break;
            }
            case AUTH_SESSION_ID_LENGTH:
            {
                int sessionIdLength = packet->getAuthSessionID().size();
                data->appendData(sessionIdLength, LEN_AUTH_SESSION_ID_LENGTH);
                data->appendData(packet->getAuthSessionID(), sessionIdLength);

                //skip dummy
                i++;
                break;
            }
            case ORIGINAL_PACKETID_LENGTH:
            {
                int originalPacketIdLength = packet->getOriginalPacketID().size();
                data->appendData(originalPacketIdLength, LEN_ORIGINAL_PACKETID_LENGTH);
                data->appendData(packet->getOriginalPacketID(), originalPacketIdLength);
                
                i++;
                break;
            }
            case PLATFORM:
            {
                data->appendData(packet->getDevice(), LEN_PLATFORM);
                break;
            }
            case FRIEND_PLATFORM:
            {
                data->appendData(packet->getFriendDevice(), LEN_FRIEND_PLATFORM);
                break;
            }
            case CHAT_BINDING_PORT:
            {
                data->appendData(packet->getChatBindingPort(), LEN_CHAT_BINDING_PORT);
                break;
            }   
            case SERVER_DATE:
            {
                data->appendData(packet->getServerDate(), LEN_SERVER_DATE);
                break;
            }   
            case GROUPID:
            {
                data->appendData(packet->getGroupId(), LEN_GROUPID);
                break;
            }
            case LEAVE_TYPE:
            {
                data->appendData(packet->getGroupLeaveType(), LEN_LEAVE_TYPE);
                break;
            }
            case ONLINE_STATUS:
            {
                data->appendData(packet->getOnlineStatus(), LEN_ONLINE_STATUS);
                break;
            }   
            case MESSAGE_TYPE:
            {
                //cout<<"setting messagetype "<<packet->getMessage()<<endl;
                data->appendData(packet->getMessageType(), LEN_MESSAGE_TYPE);
                break;
            }
			case TYPE:
			{
				data->appendData(packet->getType(), LEN_TYPE);
				break;
			}

			case INFORMATION_TYPE:
			{
				data->appendData(packet->getInformationType(), LEN_INFORMATION_TYPE);
				break;
			}

            case TIMEOUT:
            {
                data->appendData(packet->getTimeout(), LEN_TIMEOUT);
                break;
            }   
            case MESSAGE_LENGTH:
            {
                int messageLength = packet->getMessage().size();
                data->appendData(messageLength, LEN_MESSAGE_LENGTH);
                data->appendData(packet->getMessage(), messageLength);
                
                //skip dummy
                i++;
                break;
            }
			case INFORMATION_LENGTH:
			{
				int informationLength = packet->getInformation().size();
				data->appendData(informationLength, LEN_INFORMATION_LENGTH);
				data->appendData(packet->getInformation(), informationLength);
				i++;
				break;
			}
            case MESSAGE_DATE:
            {
                data->appendData(packet->getMessageDate(), LEN_MESSAGE_DATE);
                break;
            } 
            case LAST_SYNC_TIME:
            {
                data->appendData(packet->getLastSyncTime(), LEN_LAST_SYNC_TIME);
                break;
            }
            case NUMBER_OF_MESSAGES:
            {
                std::vector<std::shared_ptr<PacketDTO>> packets = packet->getMessageList();
                data->appendData((int) packets.size(), LEN_NUMBER_OF_MESSAGES);
                
                i++;
                byte innerFormatType = format[i];
                //cout<<"inner format "<<innerFormatType<<endl;
                //cout<<"Number of message "<<packets.size()<<endl;
                for (std::vector<std::shared_ptr<PacketDTO>>::size_type j = 0; j < packets.size(); j++)
                {
                    //preserve actual type
                    byte actualPacketType = packets[j]->getPacketType();
                    
                    //set inner packet type
                    packets[j]->setPacketType(innerFormatType);
                    
                    //parse
                    std::shared_ptr<ByteArray> parsedData = parse(packets[j]);
                    
                    //restore actual type
                    (*parsedData)[0] = actualPacketType;
                    
                    data->appendByteArray(parsedData);
                }
                break;
            }   
            case NUMBER_OF_CONVERSATION:
            {
                std::vector<ConversationDTO> conversationList = packet->getConversationList();
                data->appendData((int) conversationList.size(), LEN_NUMBER_OF_CONVERSATION);
                
                for (std::vector<ConversationDTO>::size_type k = 0; k < conversationList.size(); k++ )
                {
                    data->appendData(conversationList[k].GetConversationType(), LEN_CONVERSATION_TYPE);
                    
                    if(conversationList[k].GetConversationType() == ConversationType::FRIEND_ID){
                        data->appendData(conversationList[k].GetFriendId(), LEN_USER_IDENTITY);
                    }
                    else if(conversationList[k].GetConversationType() == ConversationType::GROUP_ID){
                        data->appendData(conversationList[k].GetGroupId(), LEN_GROUPID);
                    }
                    else{
                        return nullptr;
                    }
                }
                break;
            }
            case TOTAL_NUMBER_OF_PACKETS:
            {
                data->appendData(packet->getNumberOfMessage(), LEN_TOTAL_NUMBER_OF_PACKETS);
                break;
            }   
            case SEQUENCE_NUMBER:
            {
                data->appendData(packet->getSequenceNumber(), LEN_SEQUENCE_NUMBER);
                break;
            }   
            case NUMBER_OF_PACKETS:
            {
                std::vector<std::string> packetIds = packet->getPacketIDs();
                data->appendData((int)packetIds.size(), LEN_NUMBER_OF_PACKETS);

                for (std::vector<std::string>::size_type j = 0; j < packetIds.size(); j++)
                {
                    int packetIdLength = packetIds[j].size();
                    data->appendData(packetIdLength, LEN_PACKETID_LENGTH);
                    data->appendData(packetIds[j], packetIdLength);
                }

                break;
            } 
            case NUMBER_OF_SEEN_PACKET:
            {
                std::vector<SeenPacketDTO> packetDtos = packet->getSeenMessageList();
                data->appendData((int)packetDtos.size(), LEN_NUMBER_OF_SEEN_PACKET);
                
                for (std::vector<SeenPacketDTO>::size_type j = 0; j < packetDtos.size(); j++)
                {
                    int packetIdLength = packetDtos[j].getPacketID().size();
                    data->appendData(packetIdLength, LEN_PACKETID_LENGTH);
                    data->appendData(packetDtos[j].getPacketID(), packetIdLength);
                    data->appendData(packetDtos[j].getMessageDate(), LEN_MESSAGE_DATE);
                    data->appendData(packetDtos[j].getMessageStatus(), LEN_MESSAGE_STATUS);
                }

                break;
            }
            case FULL_NAME_LENGTH:
            {
                int fullNameLength = packet->getFullName().size();
                data->appendData(fullNameLength, LEN_FULL_NAME_LENGTH);
                data->appendData(packet->getFullName(), fullNameLength);
                
                //skip dummy
                i++;
                break;
            }   
            case NUMBER_OF_MEMBERS_DTO:
            {
                std::vector<MemberDTO> memberList = packet->getMemberList();
                data->appendData((int) memberList.size(), LEN_NUMBER_OF_MEMBERS_DTO);
                int len = memberList.size();
                for (int j=0; j<len; j++)
                {
                    data->appendData(memberList[j].getMemberIdentity(), LEN_USER_IDENTITY);
                    data->appendData(memberList[j].getRingId(), LEN_RING_ID);
                    std::string name = memberList[j].getFullName();
                    data->appendData((int) name.size(), LEN_MEMBER_NAME_LENGTH);
                    data->appendData(name, name.size());
                    data->appendData(memberList[j].getStatus(), LEN_MEMBER_STATUS);
                    data->appendData(memberList[j].getAddedBy(), LEN_USER_IDENTITY);
                }
                break;
            }   
            case NUMBER_OF_MEMBERS_ID_N_S:
            {
                std::vector<MemberDTO> memberList = packet->getMemberList();
                data->appendData((int) memberList.size(), LEN_NUMBER_OF_MEMBERS_ID_N_S);
                int len = memberList.size();
                for (int j=0; j<len; j++)
                {
                    data->appendData(memberList[j].getMemberIdentity(), LEN_USER_IDENTITY);
                    data->appendData(memberList[j].getRingId(), LEN_RING_ID);
                    std::string name = memberList[j].getFullName();
                    data->appendData((int) name.size(), LEN_MEMBER_NAME_LENGTH);
                    data->appendData(name, name.size());
                    data->appendData(memberList[j].getStatus(), LEN_MEMBER_STATUS);
                }
                break;
            }
            case NUMBER_OF_MEMBERS_ID_S:
            {
                std::vector<MemberDTO> memberList = packet->getMemberList();
                data->appendData((int) memberList.size(), LEN_NUMBER_OF_MEMBERS_ID_S);
                int len = memberList.size();
                for (int j=0; j<len; j++)
                {
                    data->appendData(memberList[j].getMemberIdentity(), LEN_USER_IDENTITY);
                    data->appendData(memberList[j].getStatus(), LEN_MEMBER_STATUS);
                }
                break;
            }
            case NUMBER_OF_MEMBERS_ID:
            {
                std::vector<MemberDTO> memberList = packet->getMemberList();
                data->appendData((int) memberList.size(), LEN_NUMBER_OF_MEMBERS_ID);
                int len = memberList.size();
                for (int j=0; j<len; j++)
                {
                    data->appendData(memberList[j].getMemberIdentity(), LEN_USER_IDENTITY);
                }
                break;
            }
            case FRIEND_ONLINE_STATUS:
            {
                data->appendData(packet->getOnlineStatus(), LEN_FRIEND_ONLINE_STATUS);
                break;
            }   
            case FRIEND_APP_TYPE:
            {
                data->appendData(packet->getAppType(), LEN_FRIEND_APP_TYPE);
                break;
            }   
            case FRIEND_DEVICE_TOKEN_LENGTH:
            {
                int friendDivceTokenLength = packet->getFriendDeviceToken().size();
                data->appendData(friendDivceTokenLength, LEN_FRIEND_DEVICE_TOKEN_LENGTH);
                data->appendData(packet->getFriendDeviceToken(), friendDivceTokenLength);
                
                //skip dummy
                i++;
                break;
            }  
            case FILE_TOTAL_CHUNK:
            {
                data->appendData(packet->getFileTotalChunk(), LEN_FILE_TOTAL_CHUNK);
                break;
            }
            case FILE_CHUNK_LIST_LENGTH:
            {
                std::vector<std::pair<int,int> > chunkList = packet->getFileChunkList();
                data->appendData((int) chunkList.size(), LEN_FILE_CHUNK_LIST_LENGTH);

                for (std::vector<std::pair<int,int> >::size_type i = 0; i < chunkList.size(); i++)
                {
                    int type = (chunkList[i].first==chunkList[i].second) ? 0:1;
                    data->appendData(type, LEN_FILE_CHUNK_TYPE);
                    data->appendData(chunkList[i].first, LEN_FILE_CHUNK_CURRENT_INDEX);
                    if (type==1) 
                    {
                        data->appendData(chunkList[i].second, LEN_FILE_CHUNK_CURRENT_INDEX);
                    }
                }

                break;
            }
            case FILE_CHUNK_CURRENT_INDEX:
            {
                data->appendData(packet->getFileChunkCurrentIndex(), LEN_FILE_CHUNK_CURRENT_INDEX);
                break;
            }
            case FILE_CONTENT_LENGTH:
            {
                std::string fileContent = packet->getFileContent();
                data->appendData((int) fileContent.size(), LEN_FILE_CONTENT_LENGTH);
                data->appendData(fileContent, fileContent.size());
                
                //skip dummy
                i++;
                break;
            }
            case IS_ADD_TO_BLOCK:
            {
                data->appendData((int) packet->getIsAddToBlock(), LEN_IS_ADD_TO_BLOCK);
                break;
            }
            case GROUP_NAME_LENGTH:
            {
                std::string groupName = packet->getGroupName();
                data->appendData((int) groupName.size(), LEN_GROUP_NAME_LENGTH);
                data->appendData(groupName, groupName.size());
                
                //skip dummy
                i++;
                break;
            }
            case GROUP_URL_LENGTH:
            {
                std::string groupUrl = packet->getGroupUrl();
                data->appendData((int) groupUrl.size(), LEN_GROUP_URL_LENGTH);
                data->appendData(groupUrl, groupUrl.size());
                
                //skip dummy
                i++;
                break;
            }
            case ONLINE_MOOD:
            {
                data->appendData((int) packet->getOnlineMood(), LEN_ONLINE_MOOD);
                break;
            }
            case FILE_TRANSFER_PORT:
            {
                data->appendData(packet->getFileTransferPort(), LEN_FILE_TRANSFER_PORT);
                break;
            }
            case FILE_ID:
            {
                data->appendData(packet->getFileIdentity(), LEN_FILE_ID);
                break;
            }
            case FILE_ACCEPT_REJECT:
            {
                data->appendData(packet->isFileAcceptReject(), LEN_FILE_ACCEPT_REJECT);
                break;
            }
            case FILE_OFFSET:
            {
                data->appendData(packet->getFileOffSet(), LEN_FILE_OFFSET);
                break;
            }
            case IS_SECRET_VISIBLE:
            {
                data->appendData(packet->getIsSecretVisible(), LEN_IS_SECRET_VISIBLE);
                break;
            }
            case MESSAGE_STATUS:
            {
                data->appendData(packet->getMessageStatus(), LEN_MESSAGE_STATUS);
                break;
            }
            case BLOCK_UNBLOCK_DATE:
            {
                data->appendData(packet->getBlockUnblockDate(), LEN_BLOCK_UNBLOCK_DATE);
                break;
            }
            case DATA_BYTES:
            {
                data->appendByteArray(packet->getDataBytes());
                break;
            }
            case GROUP_UPDATE_DATE:
            {
                data->appendData(packet->getGroupUpdateDate(), LEN_GROUP_UPDATE_DATE);
                break;
            }
            case UP_DOWN:
            {
                data->appendData(packet->getUpDownStatus(), LEN_UP_DOWN);
                break;
            }
            case LIMIT:
            {
                data->appendData(packet->getLimit(), LEN_LIMIT);
                break;
            }
            case NUMBER_OF_ACTIVITY:
            {
                std::vector<GroupActivityDTO> groupActivities = packet->getGroupActivities();
                data->appendData((int) groupActivities.size(), LEN_NUMBER_OF_ACTIVITY);

                for (std::vector<GroupActivityDTO>::size_type i = 0; i < groupActivities.size(); i++)
                {
                    data->appendData(groupActivities[i].getActivityType(), LEN_ACTIVITY_TYPE);
                    data->appendData(groupActivities[i].getMemberIdentity(), LEN_USER_IDENTITY);
                    std::string groupNameOrUrlString = groupActivities[i].getGroupNameOrUrlString();
                    data->appendData((int) groupNameOrUrlString.size(), LEN_GROUP_NAME_URL_LENGTH);
                    data->appendData(groupNameOrUrlString, groupNameOrUrlString.size());
                    data->appendData(groupActivities[i].getMemberType(), LEN_MEMBER_STATUS);
                    data->appendData(groupActivities[i].getChangedByUserId(), LEN_USER_IDENTITY);
                    data->appendData(groupActivities[i].getUpdateTime(), LEN_GROUP_UPDATE_DATE);
                }
                break;
            }
            case ACTIVITY_TYPE:
            {
                int activityType = packet->getGroupActivityType();
                data->appendData(activityType, LEN_ACTIVITY_TYPE);
                
                if (activityType == GROUP_NAME_CHANGE)
                {
                    std::string groupName = packet->getGroupName();
                    data->appendData((int) groupName.size(), LEN_GROUP_NAME_LENGTH);
                    data->appendData(groupName, groupName.size());
                }
                else if (activityType == GROUP_URL_CHANGE)
                {
                    std::string groupUrl = packet->getGroupUrl();
                    data->appendData((int) groupUrl.size(), LEN_GROUP_URL_LENGTH);
                    data->appendData(groupUrl, groupUrl.size());
                }
                
                break;
            }
            case NUMBER_OF_GROUPS:
            {
                std::vector<GroupDTO> groupDTOs = packet->getGroupDTOList();
                data->appendData((int) groupDTOs.size(), LEN_NUMBER_OF_GROUPS);

                for (std::vector<GroupDTO>::size_type i = 0; i < groupDTOs.size(); i++)
                {
                    data->appendData(groupDTOs[i].getGroupId(), LEN_GROUPID);
                    
                    std::string groupName = groupDTOs[i].getGroupName();
                    data->appendData((int) groupName.size(), LEN_GROUP_NAME_LENGTH);
                    data->appendData(groupName, groupName.size());
                    
                    std::string groupUrl = groupDTOs[i].getGroupUrl();
                    data->appendData((int) groupUrl.size(), LEN_GROUP_NAME_LENGTH);
                    data->appendData(groupUrl, groupUrl.size());

                    data->appendData(groupDTOs[i].getCreatorId(), LEN_USER_IDENTITY);
                    data->appendData(0, LEN_NUMBER_OF_MEMBERS); //for now it is fixed 0 because server will not provide it.
                }
                break;
            }
            case NUMBER_OF_MEMBERS:
            {
                data->appendData(packet->getNumberOfMembers(), LEN_NUMBER_OF_MEMBERS);
                break;
            }
            case NUMBER_OF_PACKETS_D_S:
            {
                std::vector<FriendMessageStatusDTO> friendMessageStatusDTOs = packet->getFriendMessageStatusDTOList();
                data->appendData((int) friendMessageStatusDTOs.size(), LEN_NUMBER_OF_PACKETS_D_S);

                for (std::vector<FriendMessageStatusDTO>::size_type i = 0; i < friendMessageStatusDTOs.size(); i++)
                {
                    std::string packetId = friendMessageStatusDTOs[i].getPacketId();
                    data->appendData((int) packetId.size(), LEN_PACKETID_LENGTH);
                    data->appendData(packetId, packetId.size());
                    data->appendData(friendMessageStatusDTOs[i].getUpdateDate(), LEN_MESSAGE_DATE);
                    data->appendData(friendMessageStatusDTOs[i].getMessageStatus(), LEN_MESSAGE_STATUS);
                }
            }
            case APP_VERSION:
            {
                data->appendData(packet->getAppVersion(), LEN_APP_VERSION);
                break;
            }
            
            //Public Room Chat :: Added items
            
            case ROOM_IDENTITY_LENGTH:
            {
                int roomIdLength = packet->getRoomId().size();
                
                data->appendData(roomIdLength, LEN_ROOM_IDENTITY_LENGTH);
                data->appendData(packet->getRoomId(), roomIdLength);
                
                i++;
                break;
            }
            
            case ROOM_FULL_NAME_LENGTH:
            {
                int roomFullNameLength = packet->getRoomFullName().size();
                
                data->appendData(roomFullNameLength, LEN_ROOM_FULL_NAME_LENGTH);
                data->appendData(packet->getRoomFullName(), roomFullNameLength);
                
                i++;
                break;
            }
            
            case MEMBER_PROFILE_URL_LENGTH:
            {
                int urlLength = packet->getRoomUrl().size();
                
                data->appendData(urlLength, LEN_MEMBER_PROFILE_URL_LENGTH);
                data->appendData(packet->getRoomUrl(), urlLength);
                
                i++;
                break;
            }
            
            case START_INDEX:
            {
                data->appendData(packet->getStartIndex(),LEN_START_INDEX);
                break;
            }
            
            case SEARCH_NAMELENGTH:
            {
                int searchNameLength = packet->getRoomSearchName().size();
                
                data->appendData(searchNameLength, LEN_SEARCH_NAMELENGTH);
                data->appendData(packet->getRoomSearchName(), searchNameLength);
                
                i++;
                break;
            }
            
            case PUBLIC_CHAT_COUNTRY_LENGTH:
            {
                int publicChatCountryLength = packet->getCountryOfPublicChatRoom().size();
                
                data->appendData(publicChatCountryLength, LEN_PUBLIC_CHAT_COUNTRY_LENGTH);
                data->appendData(packet->getCountryOfPublicChatRoom(), publicChatCountryLength);
                
                i++;
                break;
            }
            
            case PUBLIC_CHAT_CATEGORY_LENGTH:
            {
                int publicChatCategoryLength = packet->getCategoryOfPublicChatRoom().size();
                
                data->appendData(publicChatCategoryLength, LEN_PUBLIC_ROOM_CATEGORY_LENGHT);
                data->appendData(packet->getCategoryOfPublicChatRoom(), publicChatCategoryLength);
                
                i++;
                break;
            }
            
            case NUMBER_OF_ROOM:
            {
                std::vector<RoomDTO> roomList = packet->getRoomList();
                
                data->appendData((int) roomList.size(), LEN_NUMBER_OF_ROOM);

                for (std::vector<RoomDTO>::size_type i = 0; i < roomList.size(); i++)
                {
                    std::string roomId = roomList[i].getRoomId();
                    data->appendData(roomId, roomId.size());
                    
                    std::string roomFullName = roomList[i].getRoomFullName();
                    data->appendData(roomFullName, roomFullName.size());
                    
                    std::string roomPictureUrl = roomList[i].getRoomPictureUrl();
                    data->appendData(roomPictureUrl, roomPictureUrl.size());
                }
                break;
            }
            
            case SERVER_IP_LENGTH:
            {
                int serverIpLength = packet->getServerIp().size();
                
                data->appendData(serverIpLength, LEN_SERVER_IP_LENGTH);
                data->appendData(packet->getServerIp(), serverIpLength);
                
                i++;
                break;
            }
            
            case SERVER_REGISTER_PORT:
            {
                data->appendData(packet->getServerPort(),LEN_SERVER_REGISTER_PORT);
                break;
            }
            
            case NUMBER_OF_PUBLIC_CHAT_MEMBERS:
            {
                std::vector<PublicChatMemberDTO> publicChatMemberList = packet->getPublicChatMemberList();
                
                data->appendData((int) publicChatMemberList.size(), LEN_NUMBER_OF_MEMBERS);
                
                for (std::vector<PublicChatMemberDTO>::size_type i = 0; i < publicChatMemberList.size(); i++){
                    
                    data->appendData(publicChatMemberList[i].getFakeId(), LEN_USER_IDENTITY);
                    
                    data->appendData(publicChatMemberList[i].getRingId(), LEN_USER_IDENTITY);
                    
                    data->appendData(publicChatMemberList[i].getMemberId(), LEN_USER_IDENTITY);
                    
                    std::string fullName = publicChatMemberList[i].getFullName();
                    data->appendData(fullName, fullName.size());
                    
                    std::string profileUrl = publicChatMemberList[i].getProfileUrl();
                    data->appendData(profileUrl, profileUrl.size());
                    
                    long long addedTime = publicChatMemberList[i].getAddedTime();
                    data->appendData(addedTime, LEN_MEMBER_ADDED_TIME);
                }
                
                break;
            }
            
            case MONTH: 
            {
                data->appendData(packet->getMonth(), LEN_MONTH);
                break;
            }
            
            case YEAR:
            {
                data->appendData(packet->getYear(), LEN_YEAR);
                break;
            }
            
            case PAGING_STATE_LENGTH:
            {
                int pagingStateLength = packet->getPagingState().size();
                
                data->appendData(pagingStateLength, LEN_PAGING_STATE_LENGHT);
                data->appendData(packet->getPagingState(), pagingStateLength);
                
                i++;
                break;
            }
            
            case NUMBER_OF_SHADOW_INFO_ID:
            {
                std::vector<PublicChatMemberDTO> publicChatMemberList = packet->getPublicChatMemberList();
                
                data->appendData((int) publicChatMemberList.size(), LEN_NUMBER_OF_SHADOW_INFO_ID);
                
                for (std::vector<PublicChatMemberDTO>::size_type i = 0; i < publicChatMemberList.size(); i++) {
                    
                    std::string roomId = publicChatMemberList[i].getRoomId();
                    data->appendData(roomId, roomId.size());
                    
                    data->appendData(publicChatMemberList[i].getMemberId(), LEN_USER_IDENTITY);
                    
                    data->appendData(publicChatMemberList[i].getFakeId(), LEN_USER_IDENTITY);
                    
                    std::string fullName = publicChatMemberList[i].getFullName();
                    data->appendData(fullName, fullName.size());
                    
                    std::string profileUrl = publicChatMemberList[i].getProfileUrl();
                    data->appendData(profileUrl, profileUrl.size());
                }
                
                break;
            }
            
            case NUMBER_OF_SHADOW_ID:
            {
                std::vector<UserIdentity> shadowIdList = packet->getShadowIdList();
                data->appendData((int) shadowIdList.size(), LEN_NUMBER_OF_SHADOW_ID);
                int len = shadowIdList.size();
                for (int j=0; j<len; j++)
                {
                    data->appendData(shadowIdList[j], LEN_USER_IDENTITY);
                }
                break;
            }
            
            case IOS_VOIP_PUSH:
            {
                data->appendData(packet->getIosVoipPush(), LEN_IOS_VOIP_PUSH);
                break;
            }
            
            case CONVERSATION_TYPE:
            {
                data->appendData(packet->getConversationType(), LEN_CONVERSATION_TYPE);
                break;
            }
            
            case FRIEND_GROUP_ID:
            {
                data->appendData(packet->getFriendOrGroupId(), LEN_FRIEND_GROUP_ID);
                break;
            }
            
            case FILE_DOWNLOAD_ID_LENGTH:
            {
                int fileDownloadIdLength = packet->getFileDownloadId().size();
                data->appendData(fileDownloadIdLength, LEN_FILE_DOWNLOAD_ID_LENGTH);
                data->appendData(packet->getFileDownloadId(), fileDownloadIdLength);
                i++;
                break;
            }
            
            case FILE_CHUNK_COUNT:
            {
                data->appendData(packet->getFileChunkCount(), LEN_FILE_CHUNK_COUNT);
                break;
            }
            
            case FILE_CHUNK_SIZE:
            {
                data->appendData(packet->getFileChunkSize(), LEN_FILE_CHUNK_SIZE);
                break;
            }
            
            case FILE_SIZE:
            {
                data->appendData(packet->getFileSize(), LEN_FILE_SIZE);
                break;
            }
            
            case IS_FILE_MANIFEST:
            {
                data->appendData(packet->isFileManifest(), LEN_IS_FILE_MANIFEST);
                break;
            }
            
            case FILE_CHUNK_DOWNLOAD_KEY_LENGTH:
            {
                int fileChunkDownloadKeyLength = packet->getFileChunkDownloadKey().size();
                data->appendData(fileChunkDownloadKeyLength, LEN_FILE_CHUNK_DOWNLOAD_KEY_LENGTH);
                data->appendData(packet->getFileChunkDownloadKey(), fileChunkDownloadKeyLength);
                i++;
                break;
            }
            
            case FILE_DOMAIN_TYPE:
            {
                data->appendData(packet->getFileDomainType(), LEN_FILE_DOMAIN_TYPE);
                break;
            }

            case FILE_CAPTION_LENGTH:
            {
                int fileCaptionLength = packet->getCaption().size();
                data->appendData(fileCaptionLength, LEN_FILE_CAPTION_LENGTH);
                data->appendData(packet->getCaption(), fileCaptionLength);
                i++;
                break;
            }

            case FILE_WIDTH_OR_SIZE:
            {
                data->appendData(packet->getWidthOrFileSize(), LEN_FILE_WIDTH_OR_SIZE);
                break;
            }

            case FILE_HEIGHT_OR_DURATION:
            {
                data->appendData(packet->getHeightOrDuration(), LEN_FILE_HEIGHT_OR_DURATION);
                break;
            }
                
            case NUMBER_OF_PAGE:
            {
				std::set<UserIdentity> pageIdList = packet->getPageIdList();
                data->appendData((int) pageIdList.size(), LEN_NUMBER_OF_PAGE);
                int len = (int)pageIdList.size();

				for (auto it = pageIdList.begin(); it != pageIdList.end(); it++)
				{
					data->appendData(*it, LEN_USER_IDENTITY);
				}

                break;
            }

			case PROFILE_TYPE:
			{
				data->appendData(packet->getProfileType(), LEN_PROFILE_TYPE);
				break;
			}

            case FRIEND_PROFILE_TYPE:
            {
                data->appendData(packet->getFriendProfileType(), LEN_FRIEND_PROFILE_TYPE);
                break;
            }

            case MESSAGE_DELETE_TYPE:
            {
                data->appendData(packet->getMessageDeleteType(), LEN_MESSAGE_DELETE_TYPE);
                break;
            }
                
            case DISBURSE_TIME:
            {
                data->appendData(packet->getDisburseTime(), LEN_DISBURSE_TIME);
                break;
            }
                
            case EXPIRE_TIME:
            {
                data->appendData(packet->getExpireTime(), LEN_EXPIRE_TIME);
                break;
            }
                
            case NOTICE_LENGTH:
            {
                int noticeLength = (int)packet->getNotice().size();
                data->appendData(noticeLength, LEN_NOTICE_LENGTH);
                data->appendData(packet->getNotice(), noticeLength);
                i++;

                break;
            }
                
            case ISO_COUNTRY_LENGTH:
            {
                std::vector<std::string> isoCountries = packet->getIsoList();
                std::string isoCountryString;
                for (int isoIndex = 0; isoIndex < isoCountries.size(); isoIndex++)
                {
                    if (isoIndex) isoCountryString += ",";
                    isoCountryString += isoCountries[isoIndex];
                }
                
                int isoCountriesLength = (int)isoCountryString.size();
                data->appendData(isoCountriesLength, LEN_ISO_COUNTRY_LENGTH);
                data->appendData(isoCountryString, isoCountriesLength);
                i++;
                
                break;
            }

            default:
                //report exception and return null;
                //cout<<4<<endl;
                return nullptr;
                break;
        }
    }
    
    //data.push_back(0);
    //cout<<5<<endl;
    //cout<<"bytes data : "<<data.size()<<endl;
    return data;
}

GroupActivityDTO ChatParser::parseGroupActivity(std::shared_ptr<PacketDTO> packet)
{
    GroupActivityDTO groupActivity;
    groupActivity.setActivityType(packet->getPacketType());
    groupActivity.setPacketId(packet->getPacketID());
    groupActivity.setChangedByUserId(packet->getUserIdentity());
    groupActivity.setGroupId(packet->getGroupId());
    groupActivity.setUpdateTime(packet->getMessageDate());

    std::string message = packet->getMessage();
    std::unordered_map<std::string, std::string> parsedActivity;
    parsedActivity = jsonParser(message);

    groupActivity.setMemberIdentity(toStringToLong(parsedActivity["mId"].c_str()));
    groupActivity.setMemberType(toStringToInt(parsedActivity["mT"].c_str()));
    groupActivity.setGroupNameOrUrlString(parsedActivity["n"]);
    groupActivity.setRingId(toStringToLong(parsedActivity["rId"].c_str()));
    
    return groupActivity;
}

std::unordered_map<std::string,std::string> ChatParser::jsonParser(std::string str)
{
    std::unordered_map<std::string,std::string> parsedMap;
    std::string key, value;
    
#if defined(_WIN32) || defined(_WIN32_WCE)
    char modStr[1024];
#else
    char modStr[str.size()];
#endif
    int startIndex = 0;
    int endIndex = 0;
    
    int j=0;
    bool canRemoveSpace = true;
   
    for(std::string::size_type i = 0; i < str.size(); i++)
    {
        if(str.at(i)=='\"')
        {
            canRemoveSpace = !canRemoveSpace;
        }
        
        if(str.at(i)==' ' && canRemoveSpace)
        {
            continue;
        }
        
        modStr[j++]=str.at(i);
        modStr[j]=0;
    }

    std::string finalStr(modStr);
    
    for (std::string::size_type i = 0; i < finalStr.length(); i++)
    {
        if(finalStr.at(i)==':')
        {
            startIndex = endIndex = i-1;
            while(finalStr.at(startIndex-1)!='{' && finalStr.at(startIndex-1)!=',')
            {
                startIndex--;
            }
            key = finalStr.substr(startIndex+1,endIndex-startIndex-1);
            
            endIndex = startIndex = i+1;
            while(finalStr.at(endIndex+1)!='}' && finalStr.at(endIndex+1)!=',')
            {
                endIndex++;
            }
            
            if(finalStr.at(startIndex)=='\"')
                value = finalStr.substr(startIndex+1,endIndex-startIndex-1);
            else value = finalStr.substr(startIndex,endIndex-startIndex+1);
            
            parsedMap.insert(std::pair<std::string,std::string>(key,value));
        }
    }
    
    return parsedMap;
}

long long ChatParser::toStringToLong(std::string s)
{
    std::stringstream out;
    out << s.c_str();
    
    long long returnValue;
    out >> returnValue;
    
    return returnValue;
}

int ChatParser::toStringToInt(std::string s)
{
    std::stringstream out;
    out << s.c_str();
    
    int returnValue;
    out >> returnValue;
    
    return returnValue;
}

std::vector<std::string> ChatParser::getSplittedString(std::string originalString, char delim) {
    std::stringstream ss;
    ss.str(originalString);
        
    std::string str;
    std::vector<std::string> splittedStrings;
        
    while (getline(ss, str, delim)) {
        splittedStrings.push_back(str);
    }
    return splittedStrings;
}

ChatParser::~ChatParser() {
}
}
