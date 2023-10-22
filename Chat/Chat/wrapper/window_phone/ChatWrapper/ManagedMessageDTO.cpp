#include "ManagedMessageDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedMessageDTO::ManagedMessageDTO()
	{
		this->messageDTO = new imsdk::SDKMessageDTO();
	}

	ManagedMessageDTO::ManagedMessageDTO(UserIdentity senderId, UserIdentity receiverId, long long groupId, Platform::String ^packetId, int messageType, int timeOut, Platform::String ^message, long long messageDate, Platform::String ^memberFullName, Platform::String ^memberProfileUrl, bool isSecretVisible, int messageStatus, int direction, bool isEdited, int publicChatLikeCount, bool publicChatILike, bool publicChatIReport, int unreadCount)
	{
		this->messageDTO = new imsdk::SDKMessageDTO(senderId, receiverId, groupId, DataConvertionUtility::ToNativeString(packetId), messageType, timeOut, DataConvertionUtility::ToNativeString(message), messageDate, DataConvertionUtility::ToNativeString(memberFullName), DataConvertionUtility::ToNativeString(memberProfileUrl), isSecretVisible, messageStatus, direction, isEdited, publicChatLikeCount, publicChatILike, publicChatIReport, unreadCount);
	}

	ManagedMessageDTO::ManagedMessageDTO(imsdk::SDKMessageDTO &messageDTO)
	{
		this->messageDTO = new imsdk::SDKMessageDTO();
		*this->messageDTO = messageDTO;
	}

	ManagedMessageDTO::~ManagedMessageDTO()
	{

	}

	void ManagedMessageDTO::MemberFullName::set(Platform::String ^fullName)
	{
		this->messageDTO->setMemberFullName(DataConvertionUtility::ToNativeString(fullName));
	}
	Platform::String ^ManagedMessageDTO::MemberFullName::get()
	{
		return DataConvertionUtility::ToManagedString(this->messageDTO->getMemberFullName());
	}

	void ManagedMessageDTO::MemberProfileUrl::set(Platform::String ^profileUrl)
	{
		this->messageDTO->setMemberProfileUrl(DataConvertionUtility::ToNativeString(profileUrl));
	}
	Platform::String ^ManagedMessageDTO::MemberProfileUrl::get()
	{
		return DataConvertionUtility::ToManagedString(this->messageDTO->getMemberProfileUrl());
	}

	void ManagedMessageDTO::Message::set(Platform::String ^message)
	{
		this->messageDTO->setMessage(DataConvertionUtility::ToNativeString(message));
	}
	Platform::String ^ManagedMessageDTO::Message::get()
	{
		return DataConvertionUtility::ToManagedString(this->messageDTO->getMessage());
	}

	void ManagedMessageDTO::MessageDate::set(long long messageDate)
	{
		this->messageDTO->setMessageDate(messageDate);
	}
	long long ManagedMessageDTO::MessageDate::get()
	{
		return this->messageDTO->getMessageDate();
	}

	void ManagedMessageDTO::MessageType::set(int messageType)
	{
		this->messageDTO->setMessageType(messageType);
	}
	int ManagedMessageDTO::MessageType::get()
	{
		return this->messageDTO->getMessageType();
	}

	void ManagedMessageDTO::MessageStatus::set(int messageStatus)
	{
		this->messageDTO->setMessageStatus(messageStatus);
	}
	int ManagedMessageDTO::MessageStatus::get()
	{
		return this->messageDTO->getMessageStatus();
	}

	Platform::String ^ManagedMessageDTO::PacketID::get()
	{
		return DataConvertionUtility::ToManagedString(this->messageDTO->getPacketId());
	}
	void ManagedMessageDTO::PacketID::set(Platform::String ^packetId)
	{
		this->messageDTO->setPacketId(DataConvertionUtility::ToNativeString(packetId));
	}

	void ManagedMessageDTO::SenderID::set(UserIdentity senderID)
	{
		this->messageDTO->setSenderId(senderID);
	}
	UserIdentity ManagedMessageDTO::SenderID::get()
	{
		return this->messageDTO->getSenderId();
	}

	void ManagedMessageDTO::ReceiverID::set(UserIdentity receiverID)
	{
		this->messageDTO->setReceiverId(receiverID);
	}
	UserIdentity ManagedMessageDTO::ReceiverID::get()
	{
		return this->messageDTO->getReceiverId();
	}

	void ManagedMessageDTO::Direction::set(int direction)
	{
		this->messageDTO->setDirection(direction);
	}
	int ManagedMessageDTO::Direction::get()
	{
		return this->messageDTO->getDirection();
	}

	void ManagedMessageDTO::IsSecretVisible::set(bool isSecretVisible)
	{
		this->messageDTO->setSecretVisible(isSecretVisible);
	}
	bool ManagedMessageDTO::IsSecretVisible::get()
	{
		return this->messageDTO->getIsSecretVisible();
	}

	void ManagedMessageDTO::TimeOut::set(int timeOut)
	{
		this->messageDTO->setTimeOut(timeOut);
	}
	int ManagedMessageDTO::TimeOut::get()
	{
		return this->messageDTO->getTimeOut();
	}

	void ManagedMessageDTO::IsEdited::set(bool isEdited)
	{
		this->messageDTO->setIsEdited(isEdited);
	}
	bool ManagedMessageDTO::IsEdited::get()
	{
		return this->messageDTO->getIsEdited();
	}

	void ManagedMessageDTO::TotalLikeCount::set(int likeCount)
	{
		this->messageDTO->setPublicChatLikeCount(likeCount);
	}
	int ManagedMessageDTO::TotalLikeCount::get()
	{
		return this->messageDTO->getPublicChatLikeCount();
	}

	void ManagedMessageDTO::IsILike::set(bool isILike)
	{
		this->messageDTO->setPublicChatILike(isILike);
	}
	bool ManagedMessageDTO::IsILike::get()
	{
		return this->messageDTO->isPublicChatILike();
	}

	void ManagedMessageDTO::IsIReport::set(bool isIReport)
	{
		this->messageDTO->setPublicChatIReport(isIReport);
	}
	bool ManagedMessageDTO::IsIReport::get()
	{
		return this->messageDTO->isPublicChatIReport();
	}

	void ManagedMessageDTO::GroupId::set(long long groupId)
	{
		this->messageDTO->setGroupId(groupId);
	}
	long long ManagedMessageDTO::GroupId::get()
	{
		return this->messageDTO->getGroupId();
	}

	void ManagedMessageDTO::UnreadCount::set(int likeCount)
	{
		this->messageDTO->setUnreadCount(likeCount);
	}
	int ManagedMessageDTO::UnreadCount::get()
	{
		return this->messageDTO->getUnreadCount();
	}


	Platform::String^ ManagedMessageDTO::ToDebugString()
	{
		return "MessageDTO [PacketID = " + PacketID + ", ReceiverID = " + ReceiverID + ", SenderID = " + SenderID + ", MessageType = " + MessageType + ", MessageDate = " + MessageDate + ", MessageStatus = " + MessageStatus + ", IsEdited = " + IsEdited + ", TimeOut = " + TimeOut + ", IsSecretVisible = " + IsSecretVisible + ", Direction = " + Direction + ", Message = " + Message + ", MemberFullName = " + MemberFullName + ", MemberProfileUrl = " + MemberProfileUrl + ", TotalLikeCount = " + TotalLikeCount + ", IsILike = " + IsILike + ", IsIReport = " + IsIReport + "]";
	}

	imsdk::SDKMessageDTO ManagedMessageDTO::ToNativeInstance()
	{
		return *messageDTO;
	}
}
