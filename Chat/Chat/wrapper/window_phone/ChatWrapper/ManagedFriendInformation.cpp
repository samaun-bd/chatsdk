#include "ManagedFriendInformation.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedFriendInformation::ManagedFriendInformation()
	{
		this->friendInfo = new imsdk::FriendInformation(nullptr, 0, 0, 0, 0, 0, false, nullptr, nullptr, 0);
	}

	ManagedFriendInformation::ManagedFriendInformation(String ^registerServerAddress, int registerServerPort, int chatServerPort, int deviceType, int status, int mood, bool blockStatus, String ^friendName, String ^friendUrl, int profileType)
	{
		this->friendInfo = new imsdk::FriendInformation(DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort, chatServerPort, deviceType, status, mood, blockStatus, DataConvertionUtility::ToNativeString(friendName), DataConvertionUtility::ToNativeString(friendUrl), profileType);
	}

	ManagedFriendInformation::ManagedFriendInformation(imsdk::FriendInformation &friendInfo)
	{
		this->friendInfo = new imsdk::FriendInformation(friendInfo.getFriendRegisterServerAddress(), friendInfo.getFriendRegisterServerPort(), friendInfo.getFriendChatServerPort(), friendInfo.getFriendDeviceType(), friendInfo.getFriendStatus(), friendInfo.getFriendMood(), friendInfo.getBlockStatus(), friendInfo.getFriendName(), friendInfo.getFriendUrl(), friendInfo.getProfileType());
	}

	ManagedFriendInformation::~ManagedFriendInformation()
	{
	}

	String ^ManagedFriendInformation::RegisterServerAddress::get()
	{
		return DataConvertionUtility::ToManagedString(friendInfo->getFriendRegisterServerAddress());
	}

	int ManagedFriendInformation::RegisterServerPort::get()
	{
		return friendInfo->getFriendRegisterServerPort();
	}

	int ManagedFriendInformation::ChatServerPort::get()
	{
		return friendInfo->getFriendChatServerPort();
	}

	int ManagedFriendInformation::DeviceType::get()
	{
		return friendInfo->getFriendDeviceType();
	}

	int ManagedFriendInformation::Presence::get()
	{
		return friendInfo->getFriendStatus();
	}

	int ManagedFriendInformation::Mood::get()
	{
		return friendInfo->getFriendMood();
	}

	bool ManagedFriendInformation::BlockStatus::get()
	{
		return friendInfo->getBlockStatus();
	}

	String ^ManagedFriendInformation::FriendName::get()
	{
		return DataConvertionUtility::ToManagedString(friendInfo->getFriendName());
	}

	String ^ManagedFriendInformation::FriendUrl::get()
	{
		return DataConvertionUtility::ToManagedString(friendInfo->getFriendUrl());
	}

	int ManagedFriendInformation::profileType::get()
	{
		return friendInfo->getProfileType();
	}

	String^ ManagedFriendInformation::ToString()
	{
		return "FriendInformation [RegisterServerAddress = " + RegisterServerAddress + ", RegisterServerPort = " + RegisterServerPort + ", ChatServerPort = " + ChatServerPort + ", DeviceType = " + DeviceType + ", Presence = " + Presence + ", Mood = " + Mood + ", FriendName = " + FriendName + ", FriendUrl = " + FriendUrl + "]";
	}

	imsdk::FriendInformation ManagedFriendInformation::ToNativeInstance()
	{
		return *friendInfo;
	}
}
