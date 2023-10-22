#include "ManagedGroupDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedGroupDTO::ManagedGroupDTO()
	{
		this->groupDTO = new imsdk::GroupDTO();
	}

	ManagedGroupDTO::ManagedGroupDTO(imsdk::GroupDTO &groupDTO)
	{
		this->groupDTO = new imsdk::GroupDTO();
		*this->groupDTO = groupDTO;
	}

	ManagedGroupDTO::~ManagedGroupDTO()
	{
	}


	void ManagedGroupDTO::CreatorID::set(long long creatorId)
	{
		this->groupDTO->setCreatorId(creatorId);
	}

	long long ManagedGroupDTO::CreatorID::get()
	{
		return this->groupDTO->getCreatorId();
	}

	void ManagedGroupDTO::GroupUrl::set(Platform::String ^groupUrl)
	{
		this->groupDTO->setGroupUrl(DataConvertionUtility::ToNativeString(groupUrl));
	}

	Platform::String ^ManagedGroupDTO::GroupUrl::get()
	{
		return DataConvertionUtility::ToManagedString(this->groupDTO->getGroupUrl());
	}

	void ManagedGroupDTO::GroupName::set(Platform::String ^groupName)
	{
		this->groupDTO->setGroupName(DataConvertionUtility::ToNativeString(groupName));
	}

	Platform::String ^ManagedGroupDTO::GroupName::get()
	{
		return DataConvertionUtility::ToManagedString(this->groupDTO->getGroupName());
	}

	void ManagedGroupDTO::GroupID::set(long long groupId)
	{
		this->groupDTO->setGroupId(groupId);
	}

	long long ManagedGroupDTO::GroupID::get()
	{
		return this->groupDTO->getGroupId();
	}

	void ManagedGroupDTO::NumberOfMembers::set(int numberOfMembers)
	{
		this->groupDTO->setNumberOfMembers(numberOfMembers);
	}

	int ManagedGroupDTO::NumberOfMembers::get()
	{
		return this->groupDTO->getNumberOfMembers();
	}

	Platform::String^ ManagedGroupDTO::ToDebugString()
	{
		return "GroupDTO [GroupID = " + GroupID + ", CreatorID = " + CreatorID + ", NumberOfMembers = " + NumberOfMembers + ", GroupName = " + GroupName + ", GroupUrl = " + GroupUrl + "]";
	}

	imsdk::GroupDTO ManagedGroupDTO::ToNativeInstance()
	{
		return *groupDTO;
	}
}
