#pragma once

#include "ManagedSeenPacketDTO.h"
#include "ManagedMessageDTO.h"
#include "ManagedFriendMessageStatusDTO.h"
#include "ManagedFriendInformation.h"
#include "ManagedApiStatus.h"
#include "ManagedMemberDTO.h"
#include "ManagedGroupInformation.h"
#include "ManagedGroupActivityDTO.h"
#include "ManagedGroupDTO.h"
#include "ApiStatus.h"
#include "ManagedPacketTimeID.h"
#include "ManagedRoomDTO.h"
#include "PublicChatMemberDTO.h"
#include "ManagedPublicChatMemberDTO.h"
#include "ManagedDataCounter.h"
#include "ManagedConversationDTO.h"
#include <string>
#include <memory>
#include <set>

using namespace std;
using namespace Platform;

typedef String^ ManagedRoomIdentity;

typedef enum ManagedConversationType {
	ALL = 1,
	UNSEEN,
	FRIEND_ID,
	GROUP_ID,
};

namespace ChatWrapper
{
	class DataConvertionUtility
	{
	public:
		DataConvertionUtility();
		static String ^ToManagedString(const string &str);
		static string ToNativeString(String ^str);

		static vector<imsdk::SeenPacketDTO> ToNativeCollection(const Platform::Array<ManagedSeenPacketDTO^> ^list);
		static Platform::Array<ManagedSeenPacketDTO^>^ ToManagedCollection(const vector<imsdk::SeenPacketDTO> &vector);

		static vector<string> ToNativeCollection(const Platform::Array<Platform::String^> ^list);
		static Platform::Array<Platform::String^>^ ToManagedCollection(const vector<string> &vector);

		static vector<imsdk::SDKMessageDTO> ToNativeCollection(const Platform::Array<ManagedMessageDTO^> ^list);
		static Platform::Array<ManagedMessageDTO^>^ ToManagedCollection(const vector<imsdk::SDKMessageDTO> &vector);

		static vector<imsdk::FriendMessageStatusDTO> ToNativeCollection(const Platform::Array<ManagedFriendMessageStatusDTO^> ^list);
		static Platform::Array<ManagedFriendMessageStatusDTO^>^ ToManagedCollection(const vector<imsdk::FriendMessageStatusDTO> &vector);

		static ManagedApiStatus ^ToManagedApiStatus(imsdk::ApiStatus &apiStatus);

		static ManagedFriendInformation ^ToManagedFriendInformation(imsdk::FriendInformation &friendInfo);

		static set<long long> ToNativeCollectionSet(const Platform::Array<long long> ^list);

		static vector<long long> ToNativeCollection(const Platform::Array<long long> ^list);
		static Platform::Array<long long>^ ToManagedCollection(const vector<long long> &vector);

		static vector<imsdk::MemberDTO> ToNativeCollection(const Platform::Array<ManagedMemberDTO^> ^list);
		static Platform::Array<ManagedMemberDTO^>^ ToManagedCollection(const vector<imsdk::MemberDTO> &vector);

		static ManagedGroupInformation ^ToManagedGroupInformation(imsdk::GroupInformation &groupInfo);
		static vector<imsdk::GroupInformation> ToNativeCollection(const Platform::Array<ManagedGroupInformation^> ^list);
		static Platform::Array<ManagedGroupInformation^>^ ToManagedCollection(vector<imsdk::GroupInformation> &vector);
		static Platform::Array<ManagedGroupInformation^>^ ToManagedCollection(vector<shared_ptr<imsdk::GroupInformation>> &vector);

		static vector<imsdk::GroupActivityDTO> ToNativeCollection(const Platform::Array<ManagedGroupActivityDTO^> ^list);
		static Platform::Array<ManagedGroupActivityDTO^>^ ToManagedCollection(const vector<imsdk::GroupActivityDTO> &vector);

		static vector<imsdk::GroupDTO> ToNativeCollection(const Platform::Array<ManagedGroupDTO^> ^list);
		static Platform::Array<ManagedGroupDTO^>^ ToManagedCollection(const vector<imsdk::GroupDTO> &vector);

		static ManagedPacketTimeID ^ToManagedPacketTimeID(imsdk::PacketTimeId &packetTimeId);
		static vector<imsdk::PacketTimeId> ToNativeCollection(const Platform::Array<ManagedPacketTimeID^> ^list);
		static Platform::Array<ManagedPacketTimeID^>^ ToManagedCollection(vector<imsdk::PacketTimeId> &vector);

		static vector<imsdk::RoomDTO> ToNativeCollection(const Platform::Array<ManagedRoomDTO^> ^list);
		static Platform::Array<ManagedRoomDTO^>^ ToManagedCollection(const vector<imsdk::RoomDTO> &vector);

		static vector<imsdk::PublicChatMemberDTO> ToNativeCollection(const Platform::Array<ManagedPublicChatMemberDTO^> ^list);
		static Platform::Array<ManagedPublicChatMemberDTO^>^ ToManagedCollection(const vector<imsdk::PublicChatMemberDTO> &vector);

		static ManagedDataCounter ^ToManagedDataCounter(const imsdk::DataCounter &dataCounter);

		static imsdk::ConversationType ToNativeConversationType(int conversationType);

		static vector<imsdk::ConversationDTO> ToNativeCollection(const Platform::Array<ManagedConversationDTO^> ^list);
		static Platform::Array<ManagedConversationDTO^>^ ToManagedCollection(const vector<imsdk::ConversationDTO> &vector);

	};
}
