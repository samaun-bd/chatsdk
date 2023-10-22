#include "ManagedSeenPacketDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedSeenPacketDTO::ManagedSeenPacketDTO()
	{
		this->seenPacketDTO = new imsdk::SeenPacketDTO();
	}

	ManagedSeenPacketDTO::ManagedSeenPacketDTO(Platform::String ^packetId, long long messageDate, int messageStatus)
	{
		this->seenPacketDTO = new imsdk::SeenPacketDTO(DataConvertionUtility::ToNativeString(packetId), messageDate, messageStatus);
	}

	ManagedSeenPacketDTO::~ManagedSeenPacketDTO()
	{
	}

	ManagedSeenPacketDTO::ManagedSeenPacketDTO(imsdk::SeenPacketDTO &seenPacketDTO)
	{
		this->seenPacketDTO = new imsdk::SeenPacketDTO();
		*this->seenPacketDTO = seenPacketDTO;
	}

	void ManagedSeenPacketDTO::PacketID::set(Platform::String ^packetId)
	{
		this->seenPacketDTO->setPacketID(DataConvertionUtility::ToNativeString(packetId));
	}

	Platform::String ^ManagedSeenPacketDTO::PacketID::get()
	{
		return DataConvertionUtility::ToManagedString(this->seenPacketDTO->getPacketID());
	}

	void ManagedSeenPacketDTO::MessageDate::set(long long messageDate)
	{
		this->seenPacketDTO->setMessageDate(messageDate);
	}

	long long ManagedSeenPacketDTO::MessageDate::get()
	{
		return this->seenPacketDTO->getMessageDate();
	}

	void ManagedSeenPacketDTO::MessageStatus::set(int messageStatus)
	{
		this->seenPacketDTO->setMessageStatus(messageStatus);
	}

	int ManagedSeenPacketDTO::MessageStatus::get()
	{
		return this->seenPacketDTO->getMessageStatus();
	}

	Platform::String^ ManagedSeenPacketDTO::ToDebugString()
	{
		return "SeenPacketDTO [PacketID = " + PacketID + ", MessageDate = " + MessageDate + ", MessageStatus = " + MessageStatus + "]";
	}

	imsdk::SeenPacketDTO ManagedSeenPacketDTO::ToNativeInstance()
	{
		return *seenPacketDTO;
	}
}
