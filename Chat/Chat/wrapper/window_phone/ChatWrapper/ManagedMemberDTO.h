#pragma once

#include "MemberDTO.h"

namespace ChatWrapper
{
	public	ref class ManagedMemberDTO sealed
	{
	public:
		ManagedMemberDTO();
		ManagedMemberDTO(UserIdentity memberId, UserIdentity ringId, Platform::String ^fullName, int status, UserIdentity addedBy);
		virtual ~ManagedMemberDTO();

		property UserIdentity AddedBy { UserIdentity get(); void set(UserIdentity value); }
		property int Status { int get(); void set(int value); }
		property Platform::String^ FullName { Platform::String^ get(); void set(Platform::String^ value); }
		property UserIdentity MemberIdentity { UserIdentity get(); void set(UserIdentity value); }
		property long long SeenTime { long long get(); void set(long long value); }
		property UserIdentity RingId { UserIdentity get(); void set(UserIdentity value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedMemberDTO(imsdk::MemberDTO &memberDTO);
		imsdk::MemberDTO ToNativeInstance();
	private:
		imsdk::MemberDTO *memberDTO;

	};
}

