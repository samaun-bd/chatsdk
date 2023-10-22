#include "ManagedMemberDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedMemberDTO::ManagedMemberDTO()
	{
		this->memberDTO = new imsdk::MemberDTO();
	}

	ManagedMemberDTO::ManagedMemberDTO(UserIdentity memberId, UserIdentity ringId, Platform::String ^fullName, int status, UserIdentity addedBy)
	{
		this->memberDTO = new imsdk::MemberDTO(memberId, ringId, DataConvertionUtility::ToNativeString(fullName), status, addedBy);
	}

	ManagedMemberDTO::ManagedMemberDTO(imsdk::MemberDTO &memberDTO)
	{
		this->memberDTO = new imsdk::MemberDTO();
		*this->memberDTO = memberDTO;
	}

	ManagedMemberDTO::~ManagedMemberDTO()
	{
	}

	void ManagedMemberDTO::AddedBy::set(UserIdentity addedBy)
	{
		this->memberDTO->setAddedBy(addedBy);
	}

	UserIdentity ManagedMemberDTO::AddedBy::get()
	{
		return this->memberDTO->getAddedBy();
	}

	void ManagedMemberDTO::Status::set(int status)
	{
		this->memberDTO->setStatus(status);
	}

	int ManagedMemberDTO::Status::get()
	{
		return this->memberDTO->getStatus();
	}

	void ManagedMemberDTO::FullName::set(Platform::String ^fullName)
	{
		this->memberDTO->setFullName(DataConvertionUtility::ToNativeString(fullName));
	}

	Platform::String ^ManagedMemberDTO::FullName::get()
	{
		return DataConvertionUtility::ToManagedString(this->memberDTO->getFullName());
	}

	void ManagedMemberDTO::MemberIdentity::set(UserIdentity memberIdentity)
	{
		this->memberDTO->setMemberIdentity(memberIdentity);
	}

	UserIdentity ManagedMemberDTO::MemberIdentity::get()
	{
		return this->memberDTO->getMemberIdentity();
	}

	void ManagedMemberDTO::SeenTime::set(long long seenTime)
	{
		this->memberDTO->setSeenTime(seenTime);
	}

	long long ManagedMemberDTO::SeenTime::get()
	{
		return this->memberDTO->getSeenTime();
	}

	void ManagedMemberDTO::RingId::set(UserIdentity ringId)
	{
		this->memberDTO->setRingId(ringId);
	}

	UserIdentity ManagedMemberDTO::RingId::get()
	{
		return this->memberDTO->getRingId();
	}


	Platform::String^ ManagedMemberDTO::ToDebugString()
	{
		return "MemberDTO [MemberIdentity = " + MemberIdentity + ", Status = " + Status + ", AddedBy = " + AddedBy + ", FullName = " + FullName + ", SeenTime = " + SeenTime + ", RingId = " + RingId + "]";
	}

	imsdk::MemberDTO ManagedMemberDTO::ToNativeInstance()
	{
		return *memberDTO;
	}
}
