#pragma once
//#include "Types.h"
#include "ConversationDTO.h"

namespace ChatWrapper
{
	public ref class ManagedConversationDTO sealed
	{
		public:
			ManagedConversationDTO();
			ManagedConversationDTO(int conversationType, UserIdentity friendId, GroupIdentity groupId);
			virtual ~ManagedConversationDTO();

			property GroupIdentity GroupId { GroupIdentity get(); void set(GroupIdentity value); }
			property UserIdentity FriendId { UserIdentity get(); void set(UserIdentity value); }
			property int ConversationType { int get(); void set(int value); }

			Platform::String^ ToDebugString();

		internal:
			ManagedConversationDTO(imsdk::ConversationDTO &conversationDTO);
			imsdk::ConversationDTO ToNativeInstance();
		private:
			imsdk::ConversationDTO *conversationDTO;

	};
}

