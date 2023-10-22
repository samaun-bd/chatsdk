#include "ManagedGroupActivityDTO.h"
#include "DataConvertionUtility.h"


namespace ChatWrapper
{
	ManagedGroupActivityDTO::ManagedGroupActivityDTO()
	{
		this->activityDTO = new imsdk::GroupActivityDTO();
	}

	ManagedGroupActivityDTO::ManagedGroupActivityDTO(imsdk::GroupActivityDTO &activityDTO)
	{
		this->activityDTO = new imsdk::GroupActivityDTO();
		*this->activityDTO = activityDTO;
	}

	ManagedGroupActivityDTO::~ManagedGroupActivityDTO()
	{
	}

	void ManagedGroupActivityDTO::UpdateTime::set(long long updateTime)
	{
		this->activityDTO->setUpdateTime(updateTime);
	}

	long long ManagedGroupActivityDTO::UpdateTime::get()
	{
		return this->activityDTO->getUpdateTime();
	}

	void ManagedGroupActivityDTO::ChangedByUserID::set(long long changedByUserId)
	{
		this->activityDTO->setChangedByUserId(changedByUserId);
	}

	long long ManagedGroupActivityDTO::ChangedByUserID::get()
	{
		return this->activityDTO->getChangedByUserId();
	}

	void ManagedGroupActivityDTO::MemberType::set(int memberType)
	{
		this->activityDTO->setMemberType(memberType);
	}

	int ManagedGroupActivityDTO::MemberType::get()
	{
		return this->activityDTO->getMemberType();
	}

	void ManagedGroupActivityDTO::GroupNameOrUrlString::set(Platform::String ^groupNameOrUrlString)
	{
		this->activityDTO->setGroupNameOrUrlString(DataConvertionUtility::ToNativeString(groupNameOrUrlString));
	}

	Platform::String ^ManagedGroupActivityDTO::GroupNameOrUrlString::get()
	{
		return DataConvertionUtility::ToManagedString(this->activityDTO->getGroupNameOrUrlString());
	}

	void ManagedGroupActivityDTO::MemberIdentity::set(long long memberIdentity)
	{
		this->activityDTO->setMemberIdentity(memberIdentity);
	}

	long long ManagedGroupActivityDTO::MemberIdentity::get()
	{
		return this->activityDTO->getMemberIdentity();
	}

	void ManagedGroupActivityDTO::ActivityType::set(int activityType)
	{
		this->activityDTO->setActivityType(activityType);
	}

	int ManagedGroupActivityDTO::ActivityType::get()
	{
		return this->activityDTO->getActivityType();
	}

	void ManagedGroupActivityDTO::GroupID::set(long long groupId)
	{
		this->activityDTO->setGroupId(groupId);
	}

	long long ManagedGroupActivityDTO::GroupID::get()
	{
		return this->activityDTO->getGroupId();
	}

	void ManagedGroupActivityDTO::PacketID::set(Platform::String ^packetId)
	{
		this->activityDTO->setPacketId(DataConvertionUtility::ToNativeString(packetId));
	}

	Platform::String ^ManagedGroupActivityDTO::PacketID::get()
	{
		return DataConvertionUtility::ToManagedString(this->activityDTO->getPacketId());
	}


	void ManagedGroupActivityDTO::RingId::set(long long ringId)
	{
		this->activityDTO->setRingId(ringId);
	}

	long long ManagedGroupActivityDTO::RingId::get()
	{
		return this->activityDTO->getRingId();
	}


	Platform::String^ ManagedGroupActivityDTO::ToDebugString()
	{
		return "GroupActivityDTO [PacketID = " + PacketID + ", GroupID = " + GroupID + ", MemberIdentity = " + MemberIdentity + ", MemberType = " + MemberType + ", ActivityType = " + ActivityType + ", ChangedByUserID = " + ChangedByUserID + ", UpdateTime = " + UpdateTime + ", GroupNameOrUrlString = " + GroupNameOrUrlString + ", RingId = " + RingId + "]";
	}

	imsdk::GroupActivityDTO ManagedGroupActivityDTO::ToNativeInstance()
	{
		return *activityDTO;
	}
}
