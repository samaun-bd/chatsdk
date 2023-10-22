#pragma once
#include "SDKMessageDTO.h"

namespace ChatWrapper
{
	public ref class ManagedMessageDTO sealed
	{
	public:
		ManagedMessageDTO();
		ManagedMessageDTO(UserIdentity senderId, UserIdentity receiverId, long long groupId, Platform::String ^packetId, int messageType, int timeOut, Platform::String ^message, long long messageDate, Platform::String ^memberFullName, Platform::String ^memberProfileUrl, bool isSecretVisible, int messageStatus, int direction, bool isEdited, int publicChatLikeCount, bool publicChatILike, bool publicChatIReport, int unreadCount);
		virtual ~ManagedMessageDTO();
		//!ManagedMessageDTO();

		property Platform::String^ MemberFullName { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ MemberProfileUrl { Platform::String^ get(); void set(Platform::String^ value); }
		property Platform::String^ Message { Platform::String^ get(); void set(Platform::String^ value); }
		property long long MessageDate { long long get(); void set(long long value); }
		property int MessageType { int get(); void set(int value); }
		property Platform::String^ PacketID { Platform::String^ get(); void set(Platform::String^ value); }
		property UserIdentity SenderID { UserIdentity get(); void set(UserIdentity value); }
		property UserIdentity ReceiverID { UserIdentity get(); void set(UserIdentity value); }
		property int Direction { int get(); void set(int value); }
		property int MessageStatus { int get(); void set(int value); }
		property bool IsSecretVisible { bool get(); void set(bool value); }
		property int TimeOut { int get(); void set(int value); }
		property bool IsEdited { bool get(); void set(bool value); }

		property int TotalLikeCount { int get(); void set(int value); }
		property bool IsILike { bool get(); void set(bool value); }
		property bool IsIReport { bool get(); void set(bool value); }

		property long long GroupId { long long get(); void set(long long value); }
		property int UnreadCount { int get(); void set(int value); }


		Platform::String^ ToDebugString();

	internal:
		ManagedMessageDTO(imsdk::SDKMessageDTO &messageDTO);
		imsdk::SDKMessageDTO ToNativeInstance();
	private:
		imsdk::SDKMessageDTO *messageDTO;
	};
}

