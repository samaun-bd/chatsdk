#pragma once

#include "PacketTimeId.h"

namespace ChatWrapper
{
	public ref class ManagedPacketTimeID sealed
	{
	public:
		ManagedPacketTimeID();
		virtual ~ManagedPacketTimeID();

		property Platform::String^ PacketID { Platform::String^ get(); }
		property long long PacketTime1970 { long long get(); }
		property long long PacketTime1582 { long long get(); }

		virtual Platform::String^ ToString() override;

	internal:
		ManagedPacketTimeID(imsdk::PacketTimeId &packetTimeId);
		imsdk::PacketTimeId ToNativeInstance();
	private:
		imsdk::PacketTimeId *packetTimeId;
	};
}