#pragma once
#include "FriendMessageStatusDTO.h"

namespace ChatWrapper
{
	public ref class ManagedFriendMessageStatusDTO sealed
	{
	public:
		ManagedFriendMessageStatusDTO();
		virtual ~ManagedFriendMessageStatusDTO();

		property Platform::String^ PacketID { Platform::String^ get(); void set(Platform::String^ value); }
		property int MessageStatus { int get(); void set(int value); }
		property long long UpdateDate { long long get(); void set(long long value); }

		virtual Platform::String^ ToString() override;

	internal:
		ManagedFriendMessageStatusDTO(imsdk::FriendMessageStatusDTO &statusDTO);
		imsdk::FriendMessageStatusDTO ToNativeInstance();
	private:
		imsdk::FriendMessageStatusDTO *statusDTO;
	};
}

