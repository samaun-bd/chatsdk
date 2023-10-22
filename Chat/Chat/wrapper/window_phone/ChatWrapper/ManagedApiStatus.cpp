#include "ManagedApiStatus.h"

namespace ChatWrapper
{
	ManagedApiStatus::ManagedApiStatus(String^ packetId, int chatError)
	{
		this->packetId = packetId;
		this->chatError = chatError;
	}

	ManagedApiStatus::~ManagedApiStatus()
	{

	}

	String ^ManagedApiStatus::getPacketId()
	{
		return this->packetId;
	}

	int ManagedApiStatus::getErrorCode()
	{
		return	this->chatError;
	}
}
