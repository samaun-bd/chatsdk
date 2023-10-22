/*
* File:   GroupInformation.h
* Author: noman
*
* Created on May 16, 2016, 1:12 PM
*/

#ifndef GROUPINFORMATION_H
#define	GROUPINFORMATION_H

#include <string>

#include "Types.h"

namespace imsdk{
	class GroupInformation
	{
	public:
		GroupInformation(GroupIdentity groupId, std::string serverIp, int serverPort, int chatBindingPort, long long lastActivityTime);
		~GroupInformation();
                void setGroupId(GroupIdentity groupId);
                GroupIdentity getGroupId();
		std::string getRegisterServerIp();
		void setRegisterServerIp(std::string registerServerIp);
		int getRegisterServerPort();
		void setRegisterServerPort(int registerServerPort);
		int getBindingPort();
		void setBindingPort(int bindingPort);
                void setLastActivityTime(long long lastActivityTime);
                long long getLastActivityTime();
                
	private:
                GroupIdentity groupId;
		std::string registerServerIp;
		int registerServerPort;
		int bindingPort;
                long long lastActivityTime;
	};
}
#endif /*GROUPINFORMATION_H*/
