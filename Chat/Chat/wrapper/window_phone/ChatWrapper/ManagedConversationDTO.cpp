#include "ManagedConversationDTO.h"

namespace ChatWrapper
{
	ManagedConversationDTO::ManagedConversationDTO()
	{
		this->conversationDTO = new imsdk::ConversationDTO();
	}

	ManagedConversationDTO::ManagedConversationDTO(int conversationType, UserIdentity friendId, GroupIdentity groupId)
	{
		this->conversationDTO = new imsdk::ConversationDTO(conversationType, friendId, groupId);
	}

	ManagedConversationDTO::~ManagedConversationDTO()
	{
	}


	void ManagedConversationDTO::GroupId::set(GroupIdentity groupId)
	{
		this->conversationDTO->SetGroupId(groupId);
	}

	GroupIdentity ManagedConversationDTO::GroupId::get()
	{
		return this->conversationDTO->GetGroupId();
	}


	void ManagedConversationDTO::FriendId::set(UserIdentity friendId)
	{
		this->conversationDTO->SetFriendId(friendId);
	}

	UserIdentity ManagedConversationDTO::FriendId::get()
	{
		return this->conversationDTO->GetFriendId();
	}


	void ManagedConversationDTO::ConversationType::set(int conversationType)
	{
		this->conversationDTO->SetConversationType(conversationType);
	}

	int ManagedConversationDTO::ConversationType::get()
	{
		return this->conversationDTO->GetConversationType();
	}


	Platform::String^ ManagedConversationDTO::ToDebugString()
	{
		return "GroupDTO [GroupId = " + GroupId + ", FriendId = " + FriendId + ", ConversationType = " + ConversationType + "]";
	}

	ManagedConversationDTO::ManagedConversationDTO(imsdk::ConversationDTO &conversationDTO)
	{
		this->conversationDTO = new imsdk::ConversationDTO();
		*this->conversationDTO = conversationDTO;
	}

	imsdk::ConversationDTO ManagedConversationDTO::ToNativeInstance()
	{
		return *conversationDTO;
	}

}
