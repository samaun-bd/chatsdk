#include "ManagedPacketTimeID.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedPacketTimeID::ManagedPacketTimeID()
	{
		this->packetTimeId = new imsdk::PacketTimeId();
	}

	ManagedPacketTimeID::ManagedPacketTimeID(imsdk::PacketTimeId &packetTimeId)
	{
		this->packetTimeId = new imsdk::PacketTimeId();
		*this->packetTimeId = packetTimeId;
	}

	ManagedPacketTimeID::~ManagedPacketTimeID()
	{
	}

	Platform::String ^ManagedPacketTimeID::PacketID::get()
	{
		return DataConvertionUtility::ToManagedString(this->packetTimeId->packetId);
	}

	long long ManagedPacketTimeID::PacketTime1970::get()
	{
		return this->packetTimeId->packetTime1970;
	}

	long long ManagedPacketTimeID::PacketTime1582::get()
	{
		return this->packetTimeId->packetTime1582;
	}

	Platform::String^ ManagedPacketTimeID::ToString()
	{
		return "PacketTimeID [PacketID = " + PacketID + ", PacketTime1970 = " + PacketTime1970 + ", PacketTime1582 = " + PacketTime1582 + "]";
	}

	imsdk::PacketTimeId ManagedPacketTimeID::ToNativeInstance()
	{
		return *packetTimeId;
	}
}
