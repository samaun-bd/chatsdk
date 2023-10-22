#include "ManagedGroupInformation.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedGroupInformation::ManagedGroupInformation()
	{
		this->groupInfo = new imsdk::GroupInformation(0, nullptr, 0, 0, 0);
	}

	ManagedGroupInformation::ManagedGroupInformation(GroupIdentity groupId, Platform::String ^registerServerAddress, int registerServerPort, int chatServerPort, long long lastActivityTime)
	{
		this->groupInfo = new imsdk::GroupInformation(groupId, DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort, chatServerPort, lastActivityTime);
	}

	ManagedGroupInformation::ManagedGroupInformation(imsdk::GroupInformation &groupInfo)
	{
		this->groupInfo = new imsdk::GroupInformation(groupInfo.getGroupId(), groupInfo.getRegisterServerIp(), groupInfo.getRegisterServerPort(), groupInfo.getBindingPort(), groupInfo.getLastActivityTime());
	}

	ManagedGroupInformation::~ManagedGroupInformation()
	{
	}

	void ManagedGroupInformation::GroupId::set(GroupIdentity groupId)
	{
		this->groupInfo->setGroupId(groupId);
	}

	GroupIdentity ManagedGroupInformation::GroupId::get()
	{
		return groupInfo->getGroupId();
	}

	void ManagedGroupInformation::RegisterServerAddress::set(Platform::String ^ip)
	{
		this->groupInfo->setRegisterServerIp(DataConvertionUtility::ToNativeString(ip));
	}

	Platform::String ^ManagedGroupInformation::RegisterServerAddress::get()
	{
		return DataConvertionUtility::ToManagedString(groupInfo->getRegisterServerIp());
	}

	void ManagedGroupInformation::RegisterServerPort::set(int port)
	{
		this->groupInfo->setRegisterServerPort(port);
	}

	int ManagedGroupInformation::RegisterServerPort::get()
	{
		return groupInfo->getRegisterServerPort();
	}

	void ManagedGroupInformation::ChatServerPort::set(int port)
	{
		this->groupInfo->setBindingPort(port);
	}

	int ManagedGroupInformation::ChatServerPort::get()
	{
		return groupInfo->getBindingPort();
	}

	void ManagedGroupInformation::LastActivityTime::set(long long lastActivityTime)
	{
		this->groupInfo->setLastActivityTime(lastActivityTime);
	}

	long long ManagedGroupInformation::LastActivityTime::get()
	{
		return groupInfo->getLastActivityTime();
	}


	Platform::String^ ManagedGroupInformation::ToString()
	{
		return "GroupInformation [RegisterServerAddress = " + RegisterServerAddress + ", RegisterServerPort = " + RegisterServerPort + ", ChatServerPort = " + ChatServerPort + "]";
	}

	imsdk::GroupInformation ManagedGroupInformation::ToNativeInstance()
	{
		return *groupInfo;
	}
}