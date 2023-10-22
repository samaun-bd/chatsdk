#include "ManagedFriendMessageStatusDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedFriendMessageStatusDTO::ManagedFriendMessageStatusDTO()
	{
		this->statusDTO = new imsdk::FriendMessageStatusDTO();
	}

	ManagedFriendMessageStatusDTO::ManagedFriendMessageStatusDTO(imsdk::FriendMessageStatusDTO &statusDTO)
	{
		this->statusDTO = new imsdk::FriendMessageStatusDTO();
		*this->statusDTO = statusDTO;
	}

	ManagedFriendMessageStatusDTO::~ManagedFriendMessageStatusDTO()
	{
	}

	void ManagedFriendMessageStatusDTO::MessageStatus::set(int messageStatus)
	{
		this->statusDTO->setMessageStatus(messageStatus);
	}

	int ManagedFriendMessageStatusDTO::MessageStatus::get()
	{
		return this->statusDTO->getMessageStatus();
	}

	void ManagedFriendMessageStatusDTO::UpdateDate::set(long long updateDate)
	{
		this->statusDTO->setUpdateDate(updateDate);
	}

	long long ManagedFriendMessageStatusDTO::UpdateDate::get()
	{
		return this->statusDTO->getUpdateDate();
	}

	void ManagedFriendMessageStatusDTO::PacketID::set(Platform::String ^packetId)
	{
		this->statusDTO->setPacketId(DataConvertionUtility::ToNativeString(packetId));
	}

	Platform::String ^ManagedFriendMessageStatusDTO::PacketID::get()
	{
		return DataConvertionUtility::ToManagedString(this->statusDTO->getPacketId());
	}

	Platform::String^ ManagedFriendMessageStatusDTO::ToString()
	{
		return "FriendMessageStatusDTO [PacketID = " + PacketID + ", MessageStatus = " + MessageStatus + ", UpdateDate = " + UpdateDate + "]";
	}

	imsdk::FriendMessageStatusDTO ManagedFriendMessageStatusDTO::ToNativeInstance()
	{
		return *statusDTO;
	}
}