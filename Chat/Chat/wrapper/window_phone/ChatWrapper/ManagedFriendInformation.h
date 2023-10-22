#pragma once

#include "FriendInformation.h"

using namespace Platform;

namespace ChatWrapper
{
	public ref class ManagedFriendInformation sealed
	{
	public:
	public:
		ManagedFriendInformation();
		ManagedFriendInformation(String ^registerServerAddress, int registerServerPort, int chatServerPort, int deviceType, int status, int mood, bool blockStatus, String ^friendName, String ^friendUrl, int profileType);
		virtual ~ManagedFriendInformation();
		//!ManagedFriendInformation();

		property String^ RegisterServerAddress { String^ get(); }
		property int RegisterServerPort { int get(); }
		property int ChatServerPort { int get(); }
		property int Presence { int get(); }
		property int Mood { int get(); }
		property int DeviceType { int get(); }
		property bool BlockStatus { bool get(); }
		property String^ FriendName { String^ get(); }
		property String^ FriendUrl { String^ get(); }
		property int profileType{ int get(); }

		virtual String^ ToString() override;

	internal:
		ManagedFriendInformation(imsdk::FriendInformation &friendInfo);
		imsdk::FriendInformation ToNativeInstance();

	private:
		imsdk::FriendInformation *friendInfo;
	};
}

