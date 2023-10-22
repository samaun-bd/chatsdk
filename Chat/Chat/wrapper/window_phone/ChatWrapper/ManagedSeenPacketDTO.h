#pragma once

#include "SeenPacketDTO.h"

namespace ChatWrapper
{
	public	ref class ManagedSeenPacketDTO sealed
	{
	public:
		ManagedSeenPacketDTO();
		ManagedSeenPacketDTO(Platform::String ^packetId, long long messageDate, int messageStatus);
		//ManagedSeenPacketDTO(imsdk::SeenPacketDTO &seenPacketDTO);
		virtual ~ManagedSeenPacketDTO();
		//!BaseSeenPacketDTO();

		property Platform::String^ PacketID { Platform::String^ get(); void set(Platform::String^ value); }
		property long long MessageDate { long long get(); void set(long long value); }
		property int MessageStatus { int get(); void set(int value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedSeenPacketDTO(imsdk::SeenPacketDTO &seenPacketDTO);
		imsdk::SeenPacketDTO ToNativeInstance();
	private:
		imsdk::SeenPacketDTO* seenPacketDTO;
	};
}
