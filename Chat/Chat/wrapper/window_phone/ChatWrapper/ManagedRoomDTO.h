#pragma once

#include "RoomDTO.h"
#include "ManagedMessageDTO.h"

namespace ChatWrapper
{
	public	ref class ManagedRoomDTO sealed
	{
	public:
		ManagedRoomDTO();
		ManagedRoomDTO(Platform::String ^roomId, Platform::String ^roomFullName, Platform::String ^roomPictureUrl);
		virtual ~ManagedRoomDTO();
		//!BaseRoomDTO();

		property Platform::String^ RoomImageUrl { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ RoomName { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ RoomID { Platform::String^ get(); void set(Platform::String^ value); }
		property int NumberOfMember { int get(); void set(int value); }
		property Platform::Array<ManagedMessageDTO^>^ RoomMessageList { Platform::Array<ManagedMessageDTO^>^ get(); void set(const Platform::Array<ManagedMessageDTO^>^ value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedRoomDTO(imsdk::RoomDTO &roomDTO);
		imsdk::RoomDTO ToNativeInstance();
	private:
		imsdk::RoomDTO *roomDTO;
	};
}

