#include "ManagedPublicChatMemberDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedPublicChatMemberDTO::ManagedPublicChatMemberDTO()
	{
		this->publicChatMemberDTO = new imsdk::PublicChatMemberDTO();
	}

	ManagedPublicChatMemberDTO::ManagedPublicChatMemberDTO(Platform::String ^fullName, Platform::String ^profileUrl, long long addedTime)
	{
		this->publicChatMemberDTO = new imsdk::PublicChatMemberDTO(DataConvertionUtility::ToNativeString(fullName), DataConvertionUtility::ToNativeString(profileUrl), addedTime);
	}

	ManagedPublicChatMemberDTO::ManagedPublicChatMemberDTO(imsdk::PublicChatMemberDTO &publicChatMemberDTO)
	{
		this->publicChatMemberDTO = new imsdk::PublicChatMemberDTO();
		*this->publicChatMemberDTO = publicChatMemberDTO;
	}

	ManagedPublicChatMemberDTO::~ManagedPublicChatMemberDTO()
	{
	}

	//ManagedPublicChatMemberDTO::!ManagedPublicChatMemberDTO()
	//{
	//	delete publicChatMemberDTO;
	//}

	void ManagedPublicChatMemberDTO::AddedTime::set(long long addedTime)
	{
		this->publicChatMemberDTO->setAddedTime(addedTime);
	}

	long long ManagedPublicChatMemberDTO::AddedTime::get()
	{
		return this->publicChatMemberDTO->getAddedTime();
	}

	void ManagedPublicChatMemberDTO::ProfileUrl::set(Platform::String ^profileUrl)
	{
		this->publicChatMemberDTO->setProfileUrl(DataConvertionUtility::ToNativeString(profileUrl));
	}

	Platform::String ^ManagedPublicChatMemberDTO::ProfileUrl::get()
	{
		return DataConvertionUtility::ToManagedString(this->publicChatMemberDTO->getProfileUrl());
	}

	void ManagedPublicChatMemberDTO::FullName::set(Platform::String ^fullName)
	{
		this->publicChatMemberDTO->setFullName(DataConvertionUtility::ToNativeString(fullName));
	}

	Platform::String ^ManagedPublicChatMemberDTO::FullName::get()
	{
		return DataConvertionUtility::ToManagedString(this->publicChatMemberDTO->getFullName());
	}

	void ManagedPublicChatMemberDTO::MemberID::set(UserIdentity memberId)
	{
		this->publicChatMemberDTO->setMemberId(memberId);
	}
	
	UserIdentity ManagedPublicChatMemberDTO::MemberID::get()
	{
		return this->publicChatMemberDTO->getMemberId();
	}
	
	void ManagedPublicChatMemberDTO::FakeID::set(UserIdentity fakeId)
	{
		this->publicChatMemberDTO->setFakeId(fakeId);
	}
	
	UserIdentity ManagedPublicChatMemberDTO::FakeID::get()
	{
		return this->publicChatMemberDTO->getFakeId();
	}

	void ManagedPublicChatMemberDTO::RingId::set(UserIdentity ringId)
	{
		this->publicChatMemberDTO->setRingId(ringId);
	}

	UserIdentity ManagedPublicChatMemberDTO::RingId::get()
	{
		return this->publicChatMemberDTO->getRingId();
	}

	Platform::String^ ManagedPublicChatMemberDTO::ToDebugString()
	{
		return "PublicChatMemberDTO [MemberID = " + MemberID + ", FakeID = " + FakeID + ", FullName = " + FullName + ", ProfileUrl = " + ProfileUrl + ", AddedTime = " + AddedTime + ", RingId = " + RingId + "]";
	}

	imsdk::PublicChatMemberDTO ManagedPublicChatMemberDTO::ToNativeInstance()
	{
		return *publicChatMemberDTO;
	}
}
