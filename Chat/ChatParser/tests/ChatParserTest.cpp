/*
 * File:   ChatParserTest.cpp
 * Author: dipal
 *
 * Created on Aug 4, 2015, 5:04:18 PM
 */

#include "ChatParserTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChatParserTest);

ChatParserTest::ChatParserTest() {
}

ChatParserTest::~ChatParserTest() {
}

void ChatParserTest::setUp() {
}

void ChatParserTest::tearDown() {
}

bool ChatParserTest::isEqualData(ByteArray data, ByteArray expectedData) {
    if (data.size() != expectedData.size()) return false;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] != expectedData[i]) return false;
    }

    return true;
}

void ChatParserTest::CHAT_REGISTER_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_REGISTER);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setDevice(3);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_REGISTER_ToDTO() {
    shared_ptr<PacketDTO> packet;
    ByteArray data = {1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3};
    ChatParser parser;
    packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_REGISTER, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Device ", 3, packet->getDevice());
}

void ChatParserTest::CHAT_FRIEND_UNREGISTERED_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_UNREGISTERED);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setOnlineStatus(2);
    packet->setOnlineMood(5);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 2, 5};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_UNREGISTERED_ToDTO() {
    ByteArray data = {2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 2, 5};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_UNREGISTERED, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Online status", 2, packet->getOnlineStatus());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Online mood", 5, packet->getOnlineMood());
}

void ChatParserTest::CHAT_REGISTER_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_REGISTER_CONFIRMATION);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setChatBindingPort(6784);
    packet->setServerDate(546733466);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 26, 128, 0, 0, 0, 0, 32, 150, 125, 154};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_REGISTER_CONFIRMATION_ToDTO() {
    ByteArray data = {3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 26, 128, 0, 0, 0, 0, 32, 150, 125, 154};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_REGISTER_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Chat binding port", 6784, packet->getChatBindingPort());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Server date", (ll) 546733466, packet->getServerDate());
}

void ChatParserTest::CHAT_GROUP_UNREGISTER_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_UNREGISTER);
    packet->setUserIdentity(3);
    packet->setGroupId(9);
    packet->setOnlineStatus(2);
    packet->setOnlineMood(6);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 9, 2, 6};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_UNREGISTER_ToDTO() {
    ByteArray data = {4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 9, 2, 6};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_UNREGISTER, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 9, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Online status", 2, packet->getOnlineStatus());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Online mood", 6, packet->getOnlineMood());
}

void ChatParserTest::CHAT_FRIEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND);
    packet->setUserIdentity(133);
    packet->setFriendIdentity(25567);
    packet->setPacketID("21abcd");
    packet->setMessageType(14);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("It's not who I am underneath, but what I DO that defines me");
    packet->setMessageDate(1438862986);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {5, 0, 0, 0, 0, 0, 0, 0, 133, 0, 0, 0, 0, 0, 0, 99, 223, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_ToDTO() {
    ByteArray data = {5, 0, 0, 0, 0, 0, 0, 0, 133, 0, 0, 0, 0, 0, 0, 99, 223, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 133, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 25567, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 14, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1438862986, packet->getMessageDate());
}

void ChatParserTest::CHAT_DELIVERED_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_DELIVERED);
    packet->setUserIdentity((ll) 12345678912345678);
    packet->setFriendIdentity((ll) 987654321987654);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {6, 0, 43, 220, 84, 94, 20, 214, 78, 0, 3, 130, 68, 49, 5, 224, 70, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_DELIVERED_ToDTO() {
    ByteArray data = {6, 0, 43, 220, 84, 94, 20, 214, 78, 0, 3, 130, 68, 49, 5, 224, 70, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_DELIVERED, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 12345678912345678, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 987654321987654, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_SEEN_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_SEEN);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setIsOpened(true);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expecteData = {7, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 1};
    CPPUNIT_ASSERT(isEqualData(data, expecteData));
}

void ChatParserTest::CHAT_SEEN_ToDTO() {
    ByteArray data = {7, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 1};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;
    
    /*if(packet)
        std::cout<<"Not Null"<<std::endl;
    else{
        std::cout<<"NULL packet returned"<<std::endl;
    }*/

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_SEEN, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Is Opened", true, packet->getIsOpened());
}

void ChatParserTest::CHAT_SENT_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_SENT);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {8, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_SENT_ToDTO() {
    ByteArray data = {8, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_SENT, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_TYPING_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_TYPING);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {9, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_TYPING_ToDTO() {
    ByteArray data = {9, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_TYPING, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
}

void ChatParserTest::CHAT_IDEL_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_IDEL);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {10, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_IDEL_ToDTO() {
    ByteArray data = {10, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", CHAT_IDEL, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
}

void ChatParserTest::CHAT_GROUP_REGISTER_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_REGISTER);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setDevice(4);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {12, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 4};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_REGISTER_ToDTO() {
    ByteArray data = {12, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 4};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_REGISTER, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Platform", 4, packet->getDevice());
}

void ChatParserTest::CHAT_GROUP_REG_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_REG_CONFIRMATION);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setChatBindingPort(65536);
    packet->setServerDate(1439018264);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {13, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 1, 0, 0, 0, 0, 0, 0, 85, 197, 173, 24};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_REG_CONFIRMATION_ToDTO() {
    ByteArray data = {13, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 1, 0, 0, 0, 0, 0, 0, 85, 197, 173, 24};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_REG_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Chat binding port", 65536, packet->getChatBindingPort());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Server date", (ll) 1439018264, packet->getServerDate());
}

void ChatParserTest::CHAT_GROUP_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setFullName("Bruce Wayne");
    packet->setMessageType(4);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("It's not who I am underneath, but what I DO that defines me.");
    packet->setMessageDate(1439019088);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_ToDTO() {
    ByteArray data = {14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Bruce Wayne"), packet->getFullName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me."), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439019088, packet->getMessageDate());
}

void ChatParserTest::CHAT_GROUP_DELIVERED_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_DELIVERED);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {15, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_DELIVERED_ToDTO() {
    ByteArray data = {15, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_DELIVERED, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_GROUP_SEEN_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_SEEN);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {16, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_SEEN_ToDTO() {
    ByteArray data = {16, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_SEEN, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_GROUP_SENT_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_SENT);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {17, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_SENT_ToDTO() {
    ByteArray data = {17, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_SENT, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_GROUP_TYPING_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_TYPING);
    packet->setUserIdentity(3);
    packet->setGroupId(11);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {18, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_TYPING_ToDTO() {
    ByteArray data = {18, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_TYPING, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
}

void ChatParserTest::CHAT_GROUP_IDEL_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_IDEL);
    packet->setUserIdentity(3);
    packet->setGroupId(11);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {19, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_IDEL_ToDTO() {
    ByteArray data = {19, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", CHAT_GROUP_IDEL, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_0_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_OFFLINE);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {20, 6, 50, 49, 97, 98, 99, 100, 0};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_0_ToDTO() {
    ByteArray data = {20, 6, 50, 49, 97, 98, 99, 100, 0};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", CHAT_FRIEND_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 0, (int) messages.size());
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_1_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_OFFLINE);
    packet->setPacketID("21abcd");

    vector<shared_ptr < PacketDTO>> messages;
    for (int i = 0; i < 1; i++) {
        shared_ptr<PacketDTO> p = make_shared<PacketDTO>();
        p->setPacketType(CHAT_FRIEND);
        p->setFriendIdentity(133);
        p->setPacketID("21abcd");
        p->setNumberOfMessage(7);
        p->setSequenceNumber(5);
        p->setMessageType(14);
        p->setTimeout(3600);
        p->setLatitude(23.810332);
        p->setLongitude(90.412518);
        p->setMessage("It's not who I am underneath, but what I DO that defines me");
        p->setMessageDate(1438862986);

        messages.push_back(p);
    }

    packet->setMessageList(messages);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {20, 6, 50, 49, 97, 98, 99, 100, 1, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_1_ToDTO() {
    ByteArray data = {20, 6, 50, 49, 97, 98, 99, 100, 1, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 1, (int) messages.size());

    for (int i = 0; i < messages.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND, messages[i]->getPacketType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 133, messages[i]->getFriendIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), messages[i]->getPacketID());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Total number of message", 7, messages[i]->getNumberOfMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, messages[i]->getSequenceNumber());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 14, messages[i]->getMessageType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, messages[i]->getTimeout());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, messages[i]->getLatitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, messages[i]->getLongitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), messages[i]->getMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1438862986, messages[i]->getMessageDate());
    }
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_5_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_OFFLINE);
    packet->setPacketID("21abcd");

    vector<shared_ptr < PacketDTO>> messages;
    for (int i = 0; i < 5; i++) {
        shared_ptr<PacketDTO> p = make_shared<PacketDTO>();
        p->setPacketType(CHAT_FRIEND);
        p->setFriendIdentity(133);
        p->setPacketID("21abcd");
        p->setNumberOfMessage(7);
        p->setSequenceNumber(5);
        p->setMessageType(14);
        p->setTimeout(3600);
        p->setLatitude(23.810332);
        p->setLongitude(90.412518);
        p->setMessage("It's not who I am underneath, but what I DO that defines me");
        p->setMessageDate(1438862986);

        messages.push_back(p);
    }

    packet->setMessageList(messages);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {20, 6, 50, 49, 97, 98, 99, 100, 5, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_5_ToDTO() {
    ByteArray data = {20, 6, 50, 49, 97, 98, 99, 100, 5, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 0, 0, 0, 0, 0, 0, 0, 133, 6, 50, 49, 97, 98, 99, 100, 7, 5, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 5, (int) messages.size());

    for (int i = 0; i < messages.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND, messages[i]->getPacketType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 133, messages[i]->getFriendIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), messages[i]->getPacketID());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Total number of message", 7, messages[i]->getNumberOfMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, messages[i]->getSequenceNumber());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 14, messages[i]->getMessageType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, messages[i]->getTimeout());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, messages[i]->getLatitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, messages[i]->getLongitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), messages[i]->getMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1438862986, messages[i]->getMessageDate());
    }
}

void ChatParserTest::CHAT_GROUP_OFFLINE_0_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_OFFLINE);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {21, 6, 50, 49, 97, 98, 99, 100, 0};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_OFFLINE_0_ToDTO() {
    ByteArray data = {21, 6, 50, 49, 97, 98, 99, 100, 0};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 0, (int) messages.size());
}

void ChatParserTest::CHAT_GROUP_OFFLINE_1_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_OFFLINE);
    packet->setPacketID("21abcd");

    vector<shared_ptr < PacketDTO>> messages;
    for (int i = 0; i < 1; i++) {
        shared_ptr<PacketDTO> p = make_shared<PacketDTO>();
        p->setPacketType(CHAT_GROUP);
        p->setUserIdentity(3);
        p->setGroupId(11);
        p->setPacketID("21abcd");
        p->setNumberOfMessage(7);
        p->setSequenceNumber(5);
        p->setFullName("Bruce Wayne");
        p->setMessageType(4);
        p->setTimeout(3600);
        p->setLatitude(23.810332);
        p->setLongitude(90.412518);
        p->setMessage("It's not who I am underneath, but what I DO that defines me.");
        p->setMessageDate(1439019088);

        messages.push_back(p);
    }

    packet->setMessageList(messages);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {21, 6, 50, 49, 97, 98, 99, 100, 1, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_OFFLINE_1_ToDTO() {
    ByteArray data = {21, 6, 50, 49, 97, 98, 99, 100, 1, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 1, (int) messages.size());

    for (int i = 0; i < 1; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP, messages[i]->getPacketType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, messages[i]->getUserIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, messages[i]->getGroupId());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Total number of packets", 7, messages[i]->getNumberOfMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, messages[i]->getSequenceNumber());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), messages[i]->getPacketID());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Bruce Wayne"), messages[i]->getFullName());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, messages[i]->getMessageType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, messages[i]->getLatitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, messages[i]->getLongitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me."), messages[i]->getMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439019088, messages[i]->getMessageDate());
    }
}

void ChatParserTest::CHAT_GROUP_OFFLINE_5_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_OFFLINE);
    packet->setPacketID("21abcd");

    vector<shared_ptr < PacketDTO>> messages;
    for (int i = 0; i < 5; i++) {
        shared_ptr<PacketDTO> p = make_shared<PacketDTO>();
        p->setPacketType(CHAT_GROUP);
        p->setUserIdentity(3);
        p->setGroupId(11);
        p->setPacketID("21abcd");
        p->setNumberOfMessage(7);
        p->setSequenceNumber(5);
        p->setFullName("Bruce Wayne");
        p->setMessageType(4);
        p->setTimeout(3600);
        p->setLatitude(23.810332);
        p->setLongitude(90.412518);
        p->setMessage("It's not who I am underneath, but what I DO that defines me.");
        p->setMessageDate(1439019088);

        messages.push_back(p);
    }

    packet->setMessageList(messages);
    packet->setNumberOfMessage(messages.size());

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {21, 6, 50, 49, 97, 98, 99, 100, 5, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_OFFLINE_5_ToDTO() {
    ByteArray data = {21, 6, 50, 49, 97, 98, 99, 100, 5, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80, 14, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 11, 66, 114, 117, 99, 101, 32, 87, 97, 121, 110, 101, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 60, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 46, 0, 0, 0, 0, 85, 197, 176, 80};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messages = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 5, (int) messages.size());

    for (int i = 0; i < 5; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP, messages[i]->getPacketType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, messages[i]->getUserIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, messages[i]->getGroupId());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Total number of packets", 7, messages[i]->getNumberOfMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, messages[i]->getSequenceNumber());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), messages[i]->getPacketID());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Bruce Wayne"), messages[i]->getFullName());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, messages[i]->getMessageType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, messages[i]->getLatitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, messages[i]->getLongitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me."), messages[i]->getMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439019088, messages[i]->getMessageDate());
    }
}

void ChatParserTest::CHAT_GET_OFFLINE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GET_OFFLINE);
    packet->setUserIdentity(3);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {22, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GET_OFFLINE_ToDTO() {
    ByteArray data = {22, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GET_OFFLINE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_OFFLINE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_OFFLINE_CONFIRMATION);
    packet->setPacketID("21abcd");
    packet->setMessageDate(1439268994);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {23, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 0, 85, 201, 128, 130};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_OFFLINE_CONFIRMATION_ToDTO() {
    ByteArray data = {23, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 0, 85, 201, 128, 130};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_OFFLINE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439268994, packet->getMessageDate());
}

void ChatParserTest::FRIEND_CHAT_DELETE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(FRIEND_CHAT_DELETE);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {24, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::FRIEND_CHAT_DELETE_ToDTO() {
    ByteArray data = {24, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", FRIEND_CHAT_DELETE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::FRIEND_CHAT_DELETE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(FRIEND_CHAT_DELETE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {25, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::FRIEND_CHAT_DELETE_CONFIRMATION_ToDTO() {
    ByteArray data = {25, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", FRIEND_CHAT_DELETE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_CHAT_DELETE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_CHAT_DELETE);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {26, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_CHAT_DELETE_ToDTO() {
    ByteArray data = {26, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_CHAT_DELETE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_CHAT_DELETE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_CHAT_DELETE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {27, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_CHAT_DELETE_CONFIRMATION_ToDTO() {
    ByteArray data = {27, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_CHAT_DELETE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::FRIEND_INFORMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(FRIEND_INFORMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setFullName("Captain Jack Sparrow");
    packet->setDevice(2);
    packet->setFriendDevice(4);
    packet->setOnlineStatus(7);
    packet->setOnlineMood(1);
    packet->setAppType(2);
    packet->setFriendDeviceToken("294913EC-6100-42E8-8C2D-E9F68F286ADE");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {28, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 7, 2, 0, 36, 50, 57, 52, 57, 49, 51, 69, 67, 45, 54, 49, 48, 48, 45, 52, 50, 69, 56, 45, 56, 67, 50, 68, 45, 69, 57, 70, 54, 56, 70, 50, 56, 54, 65, 68, 69, 1, 2};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::FRIEND_INFORMATION_ToDTO() {
    ByteArray data = {28, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 7, 2, 0, 36, 50, 57, 52, 57, 49, 51, 69, 67, 45, 54, 49, 48, 48, 45, 52, 50, 69, 56, 45, 56, 67, 50, 68, 45, 69, 57, 70, 54, 56, 70, 50, 56, 54, 65, 68, 69, 1, 2};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", FRIEND_INFORMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Captain Jack Sparrow"), packet->getFullName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Device", 2, packet->getDevice());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend device", 4, packet->getFriendDevice());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Online status", 7, packet->getOnlineStatus());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mood", 1, packet->getOnlineMood());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("App type", 2, packet->getAppType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Device token", string("294913EC-6100-42E8-8C2D-E9F68F286ADE"), packet->getFriendDeviceToken());
}

void ChatParserTest::FRIEND_INFORMATION_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(FRIEND_INFORMATION_CONFIRMATION);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {29, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::FRIEND_INFORMATION_CONFIRMATION_ToDTO() {
    ByteArray data = {29, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", FRIEND_INFORMATION_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::FILE_TOTAL_SEQUENCE_ToByte() {

}

void ChatParserTest::FILE_TOTAL_SEQUENCE_ToDTO() {

}

void ChatParserTest::FILE_TOTAL_SEQUENCE_CONFIRMATION_ToByte() {

}

void ChatParserTest::FILE_TOTAL_SEQUENCE_CONFIRMATION_ToDTO() {

}

void ChatParserTest::FILE_STREAM_SEND_ToByte() {

}

void ChatParserTest::FILE_STREAM_SEND_ToDTO() {

}

void ChatParserTest::FILE_STREAM_SEND_CONFIRMATION_ToByte() {

}

void ChatParserTest::FILE_STREAM_SEND_CONFIRMATION_ToDTO() {

}

void ChatParserTest::GROUP_MEMBERS_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBERS);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMembers(5);

    for (int i = 0; i < 5; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setFullName("Name" + to_string(i + 10));
        member.setStatus(6);
        member.setAddedBy(7);
        packet->appendMember(member);
    }

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {34, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 5, 0, 0, 0, 0, 0, 0, 0, 10, 6, 78, 97, 109, 101, 49, 48, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 78, 97, 109, 101, 49, 49, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 12, 6, 78, 97, 109, 101, 49, 50, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 13, 6, 78, 97, 109, 101, 49, 51, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 14, 6, 78, 97, 109, 101, 49, 52, 6, 0, 0, 0, 0, 0, 0, 0, 7};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBERS_ToDTO() {
    ByteArray data = {34, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 5, 0, 0, 0, 0, 0, 0, 0, 10, 6, 78, 97, 109, 101, 49, 48, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 78, 97, 109, 101, 49, 49, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 12, 6, 78, 97, 109, 101, 49, 50, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 13, 6, 78, 97, 109, 101, 49, 51, 6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 14, 6, 78, 97, 109, 101, 49, 52, 6, 0, 0, 0, 0, 0, 0, 0, 7};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBERS, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<MemberDTO> memberList = packet->getMemberList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members in list", 5, (int) memberList.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members", 5, (int) packet->getNumberOfMembers());

    vector<MemberDTO> actualMemberList;

    for (int i = 0; i < 5; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setFullName("Name" + to_string(i + 10));
        member.setStatus(6);
        member.setAddedBy(7);
        actualMemberList.push_back(member);
    }

    for (int i = 0; i < memberList.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Member id", actualMemberList[i].getMemberIdentity(), memberList[i].getMemberIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Name", actualMemberList[i].getFullName(), memberList[i].getFullName());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Status", actualMemberList[i].getStatus(), memberList[i].getStatus());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Added by", actualMemberList[i].getAddedBy(), memberList[i].getAddedBy());
    }
}

void ChatParserTest::GROUP_MEMBERS_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBERS_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {35, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBERS_CONFIRMATION_ToDTO() {
    ByteArray data = {35, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBERS_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GET_GROUP_MEMBERS_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GET_GROUP_MEMBERS);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {36, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GET_GROUP_MEMBERS_ToDTO() {
    ByteArray data = {36, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GET_GROUP_MEMBERS, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_MEMBER_REMOVE_LEAVE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_REMOVE_LEAVE);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMembers(3);

    for (int i = 0; i < 3; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        packet->appendMember(member);
    }
    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {37, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 12};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBER_REMOVE_LEAVE_ToDTO() {
    ByteArray data = {37, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 12};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_REMOVE_LEAVE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<MemberDTO> memberList = packet->getMemberList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members in list", 3, (int) memberList.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members", 3, (int) packet->getNumberOfMembers());

    vector<MemberDTO> actualMemberList;

    for (int i = 0; i < 3; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        actualMemberList.push_back(member);
    }

    for (int i = 0; i < memberList.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Member id", actualMemberList[i].getMemberIdentity(), memberList[i].getMemberIdentity());
    }
}

void ChatParserTest::GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {38, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION_ToDTO() {
    ByteArray data = {38, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_DELETE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_DELETE);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {39, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_DELETE_ToDTO() {
    ByteArray data = {39, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_DELETE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_DELETE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_DELETE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {40, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_DELETE_CONFIRMATION_ToDTO() {
    ByteArray data = {40, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packe type", GROUP_DELETE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::MULTIPLE_FRIEND_CHAT_DELETE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(MULTIPLE_FRIEND_CHAT_DELETE);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setPacketIDs({"abdsr", "2323434csefr", "22afwse343"});

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {41, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 5, 97, 98, 100, 115, 114, 12, 50, 51, 50, 51, 52, 51, 52, 99, 115, 101, 102, 114, 10, 50, 50, 97, 102, 119, 115, 101, 51, 52, 51};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::MULTIPLE_FRIEND_CHAT_DELETE_ToDTO() {
    ByteArray data = {41, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 5, 97, 98, 100, 115, 114, 12, 50, 51, 50, 51, 52, 51, 52, 99, 115, 101, 102, 114, 10, 50, 50, 97, 102, 119, 115, 101, 51, 52, 51};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", MULTIPLE_FRIEND_CHAT_DELETE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<string> packetIds = packet->getPacketIDs();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of packets", 3, (int) packetIds.size());
    vector<string> originalPcketIds = {"abdsr", "2323434csefr", "22afwse343"};
    for (int i = 0; i < packetIds.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", originalPcketIds[i], packetIds[i]);
    }
}

void ChatParserTest::MULTIPLE_GROUP_CHAT_DELETE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(MULTIPLE_GROUP_CHAT_DELETE);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setPacketIDs({"abdsr", "2323434csefr", "22afwse343"});

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {42, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 3, 5, 97, 98, 100, 115, 114, 12, 50, 51, 50, 51, 52, 51, 52, 99, 115, 101, 102, 114, 10, 50, 50, 97, 102, 119, 115, 101, 51, 52, 51};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::MULTIPLE_GROUP_CHAT_DELETE_ToDTO() {
    ByteArray data = {42, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 3, 5, 97, 98, 100, 115, 114, 12, 50, 51, 50, 51, 52, 51, 52, 99, 115, 101, 102, 114, 10, 50, 50, 97, 102, 119, 115, 101, 51, 52, 51};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", MULTIPLE_GROUP_CHAT_DELETE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<string> packetIds = packet->getPacketIDs();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of packets", 3, (int) packetIds.size());
    vector<string> originalPacketIds = {"abdsr", "2323434csefr", "22afwse343"};
    for (int i = 0; i < originalPacketIds.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", originalPacketIds[i], packetIds[i]);
    }
}

void ChatParserTest::FRIEND_CHAT_EDIT_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(FRIEND_CHAT_EDIT);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setMessageType(3);
    packet->setTimeout(3670);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("The only rules that really matter are these: what a man can do and what a man can't do");
    packet->setMessageDate(1439286713);


    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {43, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 14, 86, 65, 190, 123, 143, 66, 180, 211, 54, 0, 86, 84, 104, 101, 32, 111, 110, 108, 121, 32, 114, 117, 108, 101, 115, 32, 116, 104, 97, 116, 32, 114, 101, 97, 108, 108, 121, 32, 109, 97, 116, 116, 101, 114, 32, 97, 114, 101, 32, 116, 104, 101, 115, 101, 58, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 32, 100, 111, 32, 97, 110, 100, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 39, 116, 32, 100, 111, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::FRIEND_CHAT_EDIT_ToDTO() {
    ByteArray data = {43, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 14, 86, 65, 190, 123, 143, 66, 180, 211, 54, 0, 86, 84, 104, 101, 32, 111, 110, 108, 121, 32, 114, 117, 108, 101, 115, 32, 116, 104, 97, 116, 32, 114, 101, 97, 108, 108, 121, 32, 109, 97, 116, 116, 101, 114, 32, 97, 114, 101, 32, 116, 104, 101, 115, 101, 58, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 32, 100, 111, 32, 97, 110, 100, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 39, 116, 32, 100, 111, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", FRIEND_CHAT_EDIT, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 3, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3670, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("The only rules that really matter are these: what a man can do and what a man can't do"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::GROUP_CHAT_EDIT_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_CHAT_EDIT);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setFullName("Captain Jack Sparrow");
    packet->setMessageType(4);
    packet->setTimeout(3670);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("The only rules that really matter are these: what a man can do and what a man can't do");
    packet->setMessageDate(1439286713);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {44, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 86, 65, 190, 123, 143, 66, 180, 211, 54, 0, 86, 84, 104, 101, 32, 111, 110, 108, 121, 32, 114, 117, 108, 101, 115, 32, 116, 104, 97, 116, 32, 114, 101, 97, 108, 108, 121, 32, 109, 97, 116, 116, 101, 114, 32, 97, 114, 101, 32, 116, 104, 101, 115, 101, 58, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 32, 100, 111, 32, 97, 110, 100, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 39, 116, 32, 100, 111, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_CHAT_EDIT_ToDTO() {
    ByteArray data = {44, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 86, 65, 190, 123, 143, 66, 180, 211, 54, 0, 86, 84, 104, 101, 32, 111, 110, 108, 121, 32, 114, 117, 108, 101, 115, 32, 116, 104, 97, 116, 32, 114, 101, 97, 108, 108, 121, 32, 109, 97, 116, 116, 101, 114, 32, 97, 114, 101, 32, 116, 104, 101, 115, 101, 58, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 32, 100, 111, 32, 97, 110, 100, 32, 119, 104, 97, 116, 32, 97, 32, 109, 97, 110, 32, 99, 97, 110, 39, 116, 32, 100, 111, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_CHAT_EDIT, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Captain Jack Sparrow"), packet->getFullName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3670, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("The only rules that really matter are these: what a man can do and what a man can't do"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::MULTIPLE_CHAT_FOR_FRIEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(MULTIPLE_CHAT_FOR_FRIEND);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    vector<shared_ptr < PacketDTO>> messageList;
    for (int i = 0; i < 3; i++) {
        shared_ptr<PacketDTO> p = make_shared<PacketDTO>();
        p->setPacketType(CHAT_FRIEND);
        p->setPacketID("21abcd");
        p->setMessageType(14);
        p->setTimeout(3600);
        p->setLatitude(23.810332);
        p->setLongitude(90.412518);
        p->setMessage("It's not who I am underneath, but what I DO that defines me");
        p->setMessageDate(1438862986);
        messageList.push_back(p);
    }

    packet->setMessageList(messageList);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {45, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::MULTIPLE_CHAT_FOR_FRIEND_ToDTO() {
    ByteArray data = {45, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 3, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138, 5, 6, 50, 49, 97, 98, 99, 100, 14, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 195, 78, 138};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", MULTIPLE_CHAT_FOR_FRIEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<shared_ptr < PacketDTO>> messageList = packet->getMessageList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 3, (int) messageList.size());

    for (int i = 0; i < 3; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND, messageList[i]->getPacketType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), messageList[i]->getPacketID());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 14, messageList[i]->getMessageType());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, messageList[i]->getTimeout());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, messageList[i]->getLatitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, messageList[i]->getLongitude());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), messageList[i]->getMessage());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1438862986, messageList[i]->getMessageDate());
    }
}

void ChatParserTest::BROCKEN_CHAT_FOR_FRIEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(BROCKEN_CHAT_FOR_FRIEND);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(5);
    packet->setMessageType(4);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("It's not who I am underneath, but what I DO that defines me");
    packet->setMessageDate(1439286713);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {46, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 7, 5, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::BROCKEN_CHAT_FOR_FRIEND_ToDTO() {
    ByteArray data = {46, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 7, 5, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", BROCKEN_CHAT_FOR_FRIEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::BROCKEN_CHAT_FOR_GROUP_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(BROCKEN_CHAT_FOR_GROUP);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(5);
    packet->setFullName("Captain Jack Sparrow");
    packet->setMessageType(4);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("The problem is not the problem. The problem is your attitude about the problem. Do you understand?");
    packet->setMessageDate(1439286713);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {47, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 98, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 110, 111, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 121, 111, 117, 114, 32, 97, 116, 116, 105, 116, 117, 100, 101, 32, 97, 98, 111, 117, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 68, 111, 32, 121, 111, 117, 32, 117, 110, 100, 101, 114, 115, 116, 97, 110, 100, 63, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::BROCKEN_CHAT_FOR_GROUP_ToDTO() {
    ByteArray data = {47, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 98, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 110, 111, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 121, 111, 117, 114, 32, 97, 116, 116, 105, 116, 117, 100, 101, 32, 97, 98, 111, 117, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 68, 111, 32, 121, 111, 117, 32, 117, 110, 100, 101, 114, 115, 116, 97, 110, 100, 63, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packe type", BROCKEN_CHAT_FOR_GROUP, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("NUmber of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Captain Jack Sparrow"), packet->getFullName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("The problem is not the problem. The problem is your attitude about the problem. Do you understand?"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::EDIT_BROCKEN_CHAT_FOR_FRIEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(EDIT_BROCKEN_CHAT_FOR_FRIEND);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(5);
    packet->setMessageType(4);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("It's not who I am underneath, but what I DO that defines me");
    packet->setMessageDate(1439286713);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {48, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 7, 5, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::EDIT_BROCKEN_CHAT_FOR_FRIEND_ToDTO() {
    ByteArray data = {48, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 7, 5, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 59, 73, 116, 39, 115, 32, 110, 111, 116, 32, 119, 104, 111, 32, 73, 32, 97, 109, 32, 117, 110, 100, 101, 114, 110, 101, 97, 116, 104, 44, 32, 98, 117, 116, 32, 119, 104, 97, 116, 32, 73, 32, 68, 79, 32, 116, 104, 97, 116, 32, 100, 101, 102, 105, 110, 101, 115, 32, 109, 101, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", EDIT_BROCKEN_CHAT_FOR_FRIEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("It's not who I am underneath, but what I DO that defines me"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::EDIT_BROCKEN_CHAT_FOR_GROUP_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(EDIT_BROCKEN_CHAT_FOR_GROUP);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(5);
    packet->setFullName("Captain Jack Sparrow");
    packet->setMessageType(4);
    packet->setTimeout(3600);
    packet->setLatitude(23.810332);
    packet->setLongitude(90.412518);
    packet->setMessage("The problem is not the problem. The problem is your attitude about the problem. Do you understand?");
    packet->setMessageDate(1439286713);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {49, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 98, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 110, 111, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 121, 111, 117, 114, 32, 97, 116, 116, 105, 116, 117, 100, 101, 32, 97, 98, 111, 117, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 68, 111, 32, 121, 111, 117, 32, 117, 110, 100, 101, 114, 115, 116, 97, 110, 100, 63, 0, 0, 0, 0, 85, 201, 197, 185};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::EDIT_BROCKEN_CHAT_FOR_GROUP_ToDTO() {
    ByteArray data = {49, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 7, 5, 20, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 4, 14, 16, 65, 190, 123, 143, 66, 180, 211, 54, 0, 98, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 110, 111, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 84, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 32, 105, 115, 32, 121, 111, 117, 114, 32, 97, 116, 116, 105, 116, 117, 100, 101, 32, 97, 98, 111, 117, 116, 32, 116, 104, 101, 32, 112, 114, 111, 98, 108, 101, 109, 46, 32, 68, 111, 32, 121, 111, 117, 32, 117, 110, 100, 101, 114, 115, 116, 97, 110, 100, 63, 0, 0, 0, 0, 85, 201, 197, 185};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packe type", EDIT_BROCKEN_CHAT_FOR_GROUP, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("NUmber of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Full name", string("Captain Jack Sparrow"), packet->getFullName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message type", 4, packet->getMessageType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timeout", 3600, packet->getTimeout());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Latitude", (float) 23.810332, packet->getLatitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Longitude", (float) 90.412518, packet->getLongitude());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message", string("The problem is not the problem. The problem is your attitude about the problem. Do you understand?"), packet->getMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_REQUEST_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_FILE_STREAM_REQUEST);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setFileTotalChunk(5);
    packet->setNumberOfMessage(6);
    packet->setSequenceNumber(5);

    vector<pair<int, int> > chunkRanges = {
        {1, 2},
        {4, 4},
        {5, 6}
    };
    packet->setFileChunkList(chunkRanges);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {50, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 5, 6, 5, 3, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 4, 1, 0, 0, 0, 5, 0, 0, 0, 6};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_REQUEST_ToDTO() {
    ByteArray data = {50, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 5, 6, 5, 3, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 4, 1, 0, 0, 0, 5, 0, 0, 0, 6};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_FILE_STREAM_REQUEST, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File total chunk", 5, packet->getFileTotalChunk());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 6, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 5, packet->getSequenceNumber());

    vector<pair<int, int> > chunkRanges = packet->getFileChunkList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of chunk range in list", 3, (int) chunkRanges.size());

    vector<pair<int, int> > originalChunkRanges = {
        {1, 2},
        {4, 4},
        {5, 6}
    };
    for (int i = 0; i < chunkRanges.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Chunk index from", chunkRanges[i].first, originalChunkRanges[i].first);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Chunk index to", chunkRanges[i].second, originalChunkRanges[i].second);
    }
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {51, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION_ToDTO() {
    ByteArray data = {51, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_SEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_FILE_STREAM_SEND);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setFileChunkCurrentIndex(3);
    packet->setFileTotalChunk(7);
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(3);
    packet->setFileContent("when u marooned me on that god forsaken spit of land, you forgot one very important thing mate, I'm Captain Jack Sparrow!");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {52, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 0, 0, 0, 7, 7, 3, 0, 121, 119, 104, 101, 110, 32, 117, 32, 109, 97, 114, 111, 111, 110, 101, 100, 32, 109, 101, 32, 111, 110, 32, 116, 104, 97, 116, 32, 103, 111, 100, 32, 102, 111, 114, 115, 97, 107, 101, 110, 32, 115, 112, 105, 116, 32, 111, 102, 32, 108, 97, 110, 100, 44, 32, 121, 111, 117, 32, 102, 111, 114, 103, 111, 116, 32, 111, 110, 101, 32, 118, 101, 114, 121, 32, 105, 109, 112, 111, 114, 116, 97, 110, 116, 32, 116, 104, 105, 110, 103, 32, 109, 97, 116, 101, 44, 32, 73, 39, 109, 32, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 33};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_SEND_ToDTO() {
    ByteArray data = {52, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 0, 0, 0, 7, 7, 3, 0, 121, 119, 104, 101, 110, 32, 117, 32, 109, 97, 114, 111, 111, 110, 101, 100, 32, 109, 101, 32, 111, 110, 32, 116, 104, 97, 116, 32, 103, 111, 100, 32, 102, 111, 114, 115, 97, 107, 101, 110, 32, 115, 112, 105, 116, 32, 111, 102, 32, 108, 97, 110, 100, 44, 32, 121, 111, 117, 32, 102, 111, 114, 103, 111, 116, 32, 111, 110, 101, 32, 118, 101, 114, 121, 32, 105, 109, 112, 111, 114, 116, 97, 110, 116, 32, 116, 104, 105, 110, 103, 32, 109, 97, 116, 101, 44, 32, 73, 39, 109, 32, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 33};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_FILE_STREAM_SEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File chunk current index", 3, packet->getFileChunkCurrentIndex());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File total chunk", 7, packet->getFileTotalChunk());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence nummber", 3, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File content", string("when u marooned me on that god forsaken spit of land, you forgot one very important thing mate, I'm Captain Jack Sparrow!"), packet->getFileContent());
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {53, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION_ToDTO() {
    ByteArray data = {53, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_REQUEST_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_FILE_STREAM_REQUEST);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setFileTotalChunk(3);
    packet->setNumberOfMessage(3);
    packet->setSequenceNumber(1);
    packet->setFileChunkList({
        {1, 2},
        {4, 4},
        {5, 6}
    });

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {54, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 3, 1, 3, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 4, 1, 0, 0, 0, 5, 0, 0, 0, 6};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_REQUEST_ToDTO() {
    ByteArray data = {54, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 3, 1, 3, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 4, 1, 0, 0, 0, 5, 0, 0, 0, 6};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_FILE_STREAM_REQUEST, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File total chunk", 3, packet->getFileTotalChunk());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 3, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 1, packet->getSequenceNumber());

    vector<pair<int, int> > chunkRanges = packet->getFileChunkList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of chunk range in list", 3, (int) chunkRanges.size());

    vector<pair<int, int> > originalChunkRanges = {
        {1, 2},
        {4, 4},
        {5, 6}
    };
    for (int i = 0; i < chunkRanges.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Chunk index from", chunkRanges[i].first, originalChunkRanges[i].first);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Chunk index to", chunkRanges[i].second, originalChunkRanges[i].second);
    }
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {55, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION_ToDTO() {
    ByteArray data = {55, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_SEND_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_FILE_STREAM_SEND);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setFileChunkCurrentIndex(3);
    packet->setFileTotalChunk(7);
    packet->setNumberOfMessage(7);
    packet->setSequenceNumber(3);
    packet->setFileContent("when u marooned me on that god forsaken spit of land, you forgot one very important thing mate, I'm Captain Jack Sparrow!");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {56, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 0, 0, 0, 7, 7, 3, 0, 121, 119, 104, 101, 110, 32, 117, 32, 109, 97, 114, 111, 111, 110, 101, 100, 32, 109, 101, 32, 111, 110, 32, 116, 104, 97, 116, 32, 103, 111, 100, 32, 102, 111, 114, 115, 97, 107, 101, 110, 32, 115, 112, 105, 116, 32, 111, 102, 32, 108, 97, 110, 100, 44, 32, 121, 111, 117, 32, 102, 111, 114, 103, 111, 116, 32, 111, 110, 101, 32, 118, 101, 114, 121, 32, 105, 109, 112, 111, 114, 116, 97, 110, 116, 32, 116, 104, 105, 110, 103, 32, 109, 97, 116, 101, 44, 32, 73, 39, 109, 32, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 33};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_SEND_ToDTO() {
    ByteArray data = {56, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 3, 0, 0, 0, 7, 7, 3, 0, 121, 119, 104, 101, 110, 32, 117, 32, 109, 97, 114, 111, 111, 110, 101, 100, 32, 109, 101, 32, 111, 110, 32, 116, 104, 97, 116, 32, 103, 111, 100, 32, 102, 111, 114, 115, 97, 107, 101, 110, 32, 115, 112, 105, 116, 32, 111, 102, 32, 108, 97, 110, 100, 44, 32, 121, 111, 117, 32, 102, 111, 114, 103, 111, 116, 32, 111, 110, 101, 32, 118, 101, 114, 121, 32, 105, 109, 112, 111, 114, 116, 97, 110, 116, 32, 116, 104, 105, 110, 103, 32, 109, 97, 116, 101, 44, 32, 73, 39, 109, 32, 67, 97, 112, 116, 97, 105, 110, 32, 74, 97, 99, 107, 32, 83, 112, 97, 114, 114, 111, 119, 33};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_FILE_STREAM_SEND, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File chunk current index", 3, packet->getFileChunkCurrentIndex());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File total chunk", 7, packet->getFileTotalChunk());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of message", 7, packet->getNumberOfMessage());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sequence number", 3, packet->getSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("File content", string("when u marooned me on that god forsaken spit of land, you forgot one very important thing mate, I'm Captain Jack Sparrow!"), packet->getFileContent());
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {57, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION_ToDTO() {
    ByteArray data = {57, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_OFFLINE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setPacketID("21abcd");
    packet->setPacketIDs({"123456", "dfed3434", "23232cere"});

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {58, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100, 3, 6, 49, 50, 51, 52, 53, 54, 8, 100, 102, 101, 100, 51, 52, 51, 52, 9, 50, 51, 50, 51, 50, 99, 101, 114, 101};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_OFFLINE_CONFIRMATION_ToDTO() {
    ByteArray data = {58, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100, 3, 6, 49, 50, 51, 52, 53, 54, 8, 100, 102, 101, 100, 51, 52, 51, 52, 9, 50, 51, 50, 51, 50, 99, 101, 114, 101};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_OFFLINE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<string> packetIds = packet->getPacketIDs();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of packet ids", 3, (int) packetIds.size());
    vector<string> orginalPacketIds = {"123456", "dfed3434", "23232cere"};
    for (int i = 0; i < 3; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", orginalPacketIds[i], packetIds[i]);
    }
}

void ChatParserTest::CHAT_GROUP_OFFLINE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_GROUP_OFFLINE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setPacketID("21abcd");
    packet->setMessageDate(1439286713);
    packet->setPacketIDs({"123456", "dfed3434", "23232cere"});

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {59, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 0, 85, 201, 197, 185, 3, 6, 49, 50, 51, 52, 53, 54, 8, 100, 102, 101, 100, 51, 52, 51, 52, 9, 50, 51, 50, 51, 50, 99, 101, 114, 101};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_GROUP_OFFLINE_CONFIRMATION_ToDTO() {
    ByteArray data = {59, 0, 0, 0, 0, 0, 0, 0, 3, 6, 50, 49, 97, 98, 99, 100, 0, 0, 0, 0, 85, 201, 197, 185, 3, 6, 49, 50, 51, 52, 53, 54, 8, 100, 102, 101, 100, 51, 52, 51, 52, 9, 50, 51, 50, 51, 50, 99, 101, 114, 101};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_GROUP_OFFLINE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message date", (ll) 1439286713, packet->getMessageDate());
    vector<string> packetIds = packet->getPacketIDs();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of packet ids", 3, (int) packetIds.size());
    vector<string> orginalPacketIds = {"123456", "dfed3434", "23232cere"};
    for (int i = 0; i < 3; i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", orginalPacketIds[i], packetIds[i]);
    }
}

void ChatParserTest::CHAT_FRIEND_BLOCK_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_BLOCK);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");
    packet->setIsAddToBlock(1);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {60, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 1};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_BLOCK_ToDTO() {
    ByteArray data = {60, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100, 1};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_BLOCK, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Is add block", (bool) 1, packet->getIsAddToBlock());
}

void ChatParserTest::CHAT_FRIEND_UNBLOCK_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_FRIEND_UNBLOCK);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {61, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_FRIEND_UNBLOCK_ToDTO() {
    ByteArray data = {61, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_FRIEND_UNBLOCK, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::CHAT_BLOCK_UNBLOCK_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(CHAT_BLOCK_UNBLOCK_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setFriendIdentity(7);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {62, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::CHAT_BLOCK_UNBLOCK_CONFIRMATION_ToDTO() {
    ByteArray data = {62, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 7, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", CHAT_BLOCK_UNBLOCK_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Friend id", (ll) 7, packet->getFriendIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_MEMBER_ADD_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_ADD);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMembers(5);

    for (int i = 0; i < 5; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setFullName("Name" + to_string(i + 10));
        member.setStatus(6);
        packet->appendMember(member);
    }

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {63, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 5, 0, 0, 0, 0, 0, 0, 0, 10, 6, 78, 97, 109, 101, 49, 48, 6, 0, 0, 0, 0, 0, 0, 0, 11, 6, 78, 97, 109, 101, 49, 49, 6, 0, 0, 0, 0, 0, 0, 0, 12, 6, 78, 97, 109, 101, 49, 50, 6, 0, 0, 0, 0, 0, 0, 0, 13, 6, 78, 97, 109, 101, 49, 51, 6, 0, 0, 0, 0, 0, 0, 0, 14, 6, 78, 97, 109, 101, 49, 52, 6};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBER_ADD_ToDTO() {
    ByteArray data = {63, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 5, 0, 0, 0, 0, 0, 0, 0, 10, 6, 78, 97, 109, 101, 49, 48, 6, 0, 0, 0, 0, 0, 0, 0, 11, 6, 78, 97, 109, 101, 49, 49, 6, 0, 0, 0, 0, 0, 0, 0, 12, 6, 78, 97, 109, 101, 49, 50, 6, 0, 0, 0, 0, 0, 0, 0, 13, 6, 78, 97, 109, 101, 49, 51, 6, 0, 0, 0, 0, 0, 0, 0, 14, 6, 78, 97, 109, 101, 49, 52, 6};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_ADD, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<MemberDTO> memberList = packet->getMemberList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members in list", 5, (int) memberList.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members", 5, (int) packet->getNumberOfMembers());

    vector<MemberDTO> actualMemberList;

    for (int i = 0; i < 5; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setFullName("Name" + to_string(i + 10));
        member.setStatus(6);
        actualMemberList.push_back(member);
    }

    for (int i = 0; i < memberList.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Member id", actualMemberList[i].getMemberIdentity(), memberList[i].getMemberIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Name", actualMemberList[i].getFullName(), memberList[i].getFullName());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Status", actualMemberList[i].getStatus(), memberList[i].getStatus());
    }
}

void ChatParserTest::GROUP_MEMBER_ADD_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_ADD_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {64, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBER_ADD_CONFIRMATION_ToDTO() {
    ByteArray data = {64, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_ADD_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_INFORMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_INFORMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setGroupName("Group1");
    packet->setGroupUrl("http://image.groupapis.com/group1");
    packet->setTotalGroupMembers(95);
    packet->setIsUpdateGroupInformation(true);

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {65, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 6, 71, 114, 111, 117, 112, 49, 33, 104, 116, 116, 112, 58, 47, 47, 105, 109, 97, 103, 101, 46, 103, 114, 111, 117, 112, 97, 112, 105, 115, 46, 99, 111, 109, 47, 103, 114, 111, 117, 112, 49, 0, 95, 1};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_INFORMATION_ToDTO() {
    ByteArray data = {65, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 6, 71, 114, 111, 117, 112, 49, 33, 104, 116, 116, 112, 58, 47, 47, 105, 109, 97, 103, 101, 46, 103, 114, 111, 117, 112, 97, 112, 105, 115, 46, 99, 111, 109, 47, 103, 114, 111, 117, 112, 49, 0, 95, 1};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_INFORMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group name", string("Group1"), packet->getGroupName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group url", string("http://image.groupapis.com/group1"), packet->getGroupUrl());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Total group members", 95, packet->getTotalGroupMembers());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("IS update group information", true, packet->getIsUpdateGroupInformation());
}

void ChatParserTest::GET_GROUP_INFORMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GET_GROUP_INFORMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {66, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GET_GROUP_INFORMATION_ToDTO() {
    ByteArray data = {66, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GET_GROUP_INFORMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_INFORMATION_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_INFORMATION_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setIsUpdateGroupInformation(true);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {67, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 1};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_INFORMATION_CONFIRMATION_ToDTO() {
    ByteArray data = {67, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 1};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_INFORMATION_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Is update group information", true, packet->getIsUpdateGroupInformation());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}

void ChatParserTest::GROUP_MEMBER_STATUS_CHANGE_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_STATUS_CHANGE);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");
    packet->setNumberOfMembers(4);

    for (int i = 0; i < 4; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setStatus(6);
        packet->appendMember(member);
    }

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {68, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 4, 0, 0, 0, 0, 0, 0, 0, 10, 6, 0, 0, 0, 0, 0, 0, 0, 11, 6, 0, 0, 0, 0, 0, 0, 0, 12, 6, 0, 0, 0, 0, 0, 0, 0, 13, 6};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));

}

void ChatParserTest::GROUP_MEMBER_STATUS_CHANGE_ToDTO() {
    ByteArray data = {68, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100, 4, 0, 0, 0, 0, 0, 0, 0, 10, 6, 0, 0, 0, 0, 0, 0, 0, 11, 6, 0, 0, 0, 0, 0, 0, 0, 12, 6, 0, 0, 0, 0, 0, 0, 0, 13, 6};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_STATUS_CHANGE, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());

    vector<MemberDTO> memberList = packet->getMemberList();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members in list", 4, (int) memberList.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of members", 4, (int) packet->getNumberOfMembers());

    vector<MemberDTO> actualMemberList;

    for (int i = 0; i < 4; i++) {
        MemberDTO member;
        member.setMemberIdentity(i + 10);
        member.setStatus(6);
        actualMemberList.push_back(member);
    }

    for (int i = 0; i < memberList.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Member id", actualMemberList[i].getMemberIdentity(), memberList[i].getMemberIdentity());
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Status", actualMemberList[i].getStatus(), memberList[i].getStatus());
    }
}

void ChatParserTest::GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION_ToByte() {
    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
    packet->setPacketType(GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION);
    packet->setUserIdentity(3);
    packet->setGroupId(11);
    packet->setPacketID("21abcd");

    ChatParser parser;
    ByteArray data = *parser.parse(packet);
    ByteArray expectedData = {69, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};

    CPPUNIT_ASSERT(isEqualData(data, expectedData));
}

void ChatParserTest::GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION_ToDTO() {
    ByteArray data = {69, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 11, 6, 50, 49, 97, 98, 99, 100};
    ChatParser parser;
    shared_ptr<PacketDTO> packet = parser.parse(data).packet;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet type", GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION, packet->getPacketType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("User id", (ll) 3, packet->getUserIdentity());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Group id", (ll) 11, packet->getGroupId());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Packet id", string("21abcd"), packet->getPacketID());
}
