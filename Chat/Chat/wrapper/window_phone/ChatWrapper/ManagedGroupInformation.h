#pragma once

#include "GroupInformation.h"

namespace ChatWrapper
{
	public ref class ManagedGroupInformation sealed
	{
	public:
		ManagedGroupInformation();
		ManagedGroupInformation(GroupIdentity groupId, Platform::String ^registerServerAddress, int registerServerPort, int chatServerPort, long long lastActivityTime);
		virtual ~ManagedGroupInformation();

		property GroupIdentity GroupId { GroupIdentity get(); void set(GroupIdentity value); }
		property Platform::String^ RegisterServerAddress { Platform::String^ get(); void set(Platform::String^ value); }
		property int RegisterServerPort { int get(); void set(int value); }
		property int ChatServerPort { int get(); void set(int value); }
		property long long LastActivityTime { long long get(); void set(long long value); }

		virtual Platform::String^ ToString() override;

	internal:
		ManagedGroupInformation(imsdk::GroupInformation &groupInfo);
		imsdk::GroupInformation ToNativeInstance();

	private:
		imsdk::GroupInformation *groupInfo;
	};
}