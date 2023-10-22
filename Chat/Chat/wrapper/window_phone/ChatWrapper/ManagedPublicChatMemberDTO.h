#pragma once
#include "PublicChatMemberDTO.h"

namespace ChatWrapper
{
	public ref class ManagedPublicChatMemberDTO sealed
	{
	public:
		ManagedPublicChatMemberDTO();
		ManagedPublicChatMemberDTO(Platform::String ^fullName, Platform::String ^profileUrl, long long addedTime);
		virtual ~ManagedPublicChatMemberDTO();
		//!ManagedPublicChatMemberDTO();

		property long long AddedTime { long long get(); void set(long long value); }
		property Platform::String^ ProfileUrl { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ FullName { Platform::String^ get(); void set(Platform::String^ value); }
		property UserIdentity MemberID { UserIdentity get(); void set(UserIdentity value); }
		property UserIdentity FakeID { UserIdentity get(); void set(UserIdentity value); }
		property UserIdentity RingId { UserIdentity get(); void set(UserIdentity value); }

		Platform::String^ ToDebugString();

	internal:
		ManagedPublicChatMemberDTO(imsdk::PublicChatMemberDTO &publicChatMemberDTO);
		imsdk::PublicChatMemberDTO ToNativeInstance();
	private:
		imsdk::PublicChatMemberDTO *publicChatMemberDTO;
	};
}

