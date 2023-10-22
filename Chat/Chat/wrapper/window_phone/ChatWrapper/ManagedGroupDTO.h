#pragma once

#include "GroupDTO.h"

namespace ChatWrapper
{
	public ref class ManagedGroupDTO sealed
	{
	public:
		ManagedGroupDTO();
		virtual ~ManagedGroupDTO();

		property long long CreatorID { long long get(); void set(long long value); }
		property Platform::String^ GroupUrl { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ GroupName { Platform::String^ get(); void set(Platform::String^ value); }
		property long long GroupID { long long get(); void set(long long value); }
		property int NumberOfMembers { int get(); void set(int value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedGroupDTO(imsdk::GroupDTO &groupDTO);
		imsdk::GroupDTO ToNativeInstance();
	private:
		imsdk::GroupDTO *groupDTO;
	};
}
