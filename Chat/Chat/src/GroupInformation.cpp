/*
* File:   GroupInformation.h
* Author: noman
*
* Created on May 16, 2016, 1:12 PM
*/

#include "GroupInformation.h"

namespace imsdk{
	GroupInformation::GroupInformation(GroupIdentity groupId, std::string serverIp, int serverPort, int chatBindingPort, long long lastActivityTime) :groupId(groupId), registerServerIp(serverIp), registerServerPort(serverPort), bindingPort(chatBindingPort), lastActivityTime(lastActivityTime)
	{
	}


	GroupInformation::~GroupInformation()
	{
	}

	std::string GroupInformation::getRegisterServerIp()
	{
		return registerServerIp;
	}

	void GroupInformation::setRegisterServerIp(std::string registerServerIp)
	{
		this->registerServerIp = registerServerIp;
	}

	int GroupInformation::getRegisterServerPort()
	{
		return registerServerPort;
	}

	void GroupInformation::setRegisterServerPort(int registerServerPort)
	{
		this->registerServerPort = registerServerPort;
	}

	int GroupInformation::getBindingPort()
	{
		return bindingPort;
	}

	void GroupInformation::setBindingPort(int bindingPort)
	{
		this->bindingPort = bindingPort;
	}

        void GroupInformation::setLastActivityTime(long long lastActivityTime) {
            this->lastActivityTime = lastActivityTime;
        }

        long long GroupInformation::getLastActivityTime() {
            return lastActivityTime;
        }

        void GroupInformation::setGroupId(GroupIdentity groupId) {
            this->groupId = groupId;
        }

        GroupIdentity GroupInformation::getGroupId() {
            return groupId;
        }
}