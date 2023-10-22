#pragma once

#include "GroupActivityDTO.h"

namespace ChatWrapper
{
	public ref class ManagedGroupActivityDTO sealed
	{
	public:
		ManagedGroupActivityDTO();
		virtual ~ManagedGroupActivityDTO();

		property long long UpdateTime { long long get(); void set(long long value); }
		property long long ChangedByUserID { long long get(); void set(long long value); }
		property int MemberType { int get(); void set(int value); }
		property Platform::String^ GroupNameOrUrlString { Platform::String^ get(); void set(Platform::String^ value); }
		property long long MemberIdentity { long long get(); void set(long long value); }
		property int ActivityType { int get(); void set(int value); }
		property long long GroupID { long long get(); void set(long long value); }
		property Platform::String^ PacketID { Platform::String^ get(); void set(Platform::String^ value); }
		property long long RingId { long long get(); void set(long long value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedGroupActivityDTO(imsdk::GroupActivityDTO &activityDTO);
		imsdk::GroupActivityDTO ToNativeInstance();
	private:
		imsdk::GroupActivityDTO *activityDTO;
	};
}

