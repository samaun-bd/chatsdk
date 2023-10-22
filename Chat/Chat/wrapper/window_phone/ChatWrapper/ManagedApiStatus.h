#pragma once
#include "ApiStatus.h"

using namespace Platform;

namespace ChatWrapper
{
	public ref class ManagedApiStatus sealed
	{
	public:
		ManagedApiStatus(String^ packetId, int chatError);
		virtual ~ManagedApiStatus();

		String ^getPacketId();
		int getErrorCode();

	private:
		String^ packetId;
		int chatError;
		imsdk::ApiStatus *apiStatus;

	};

}

