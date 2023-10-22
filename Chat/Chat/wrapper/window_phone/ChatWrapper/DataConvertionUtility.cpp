#include "DataConvertionUtility.h"
#include <windows.h>

namespace ChatWrapper
{
	DataConvertionUtility::DataConvertionUtility()
	{

	}

	// Convert a wide Unicode to an UTF8 string String
	std::string utf8_encode(const std::wstring &wstr)
	{
		if (wstr.empty()) return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}

	// Convert an UTF8 string to a wide Unicode String
	std::wstring utf8_decode(const std::string &str)
	{
		if (str.empty()) return std::wstring();
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}


	String^ DataConvertionUtility::ToManagedString(const string &str)
	{
		wstring strng = utf8_decode(str);
		return ref new String(strng.c_str());
	}


	string DataConvertionUtility::ToNativeString(String ^strng)
	{
		wstring str = strng->Data();
		return utf8_encode(str);
	}


	vector<imsdk::SeenPacketDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedSeenPacketDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::SeenPacketDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedSeenPacketDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::SeenPacketDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedSeenPacketDTO^> ^tempList = ref new Platform::Array<ManagedSeenPacketDTO^>(count);
			for (unsigned int i = 0; i < count; i++)
			{
				imsdk::SeenPacketDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedSeenPacketDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	vector<string> DataConvertionUtility::ToNativeCollection(const Platform::Array<Platform::String^> ^list)
	{
		int count = list->Length;
		vector<string> vector;

		for (int i = 0; i < count; i++)
		{
			vector.push_back(ToNativeString(list[i]));
		}
		return vector;
	}

	Platform::Array<Platform::String^>^ DataConvertionUtility::ToManagedCollection(const vector<string> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<Platform::String^> ^tempList = ref new Platform::Array<Platform::String^>(count);
			for (int i = 0; i < count; i++)
			{
				tempList->set(i, ToManagedString(vector[i]));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}

	vector<imsdk::SDKMessageDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedMessageDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::SDKMessageDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedMessageDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::SDKMessageDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedMessageDTO^> ^tempList = ref new Platform::Array<ManagedMessageDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::SDKMessageDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedMessageDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}

	vector<imsdk::FriendMessageStatusDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedFriendMessageStatusDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::FriendMessageStatusDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedFriendMessageStatusDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::FriendMessageStatusDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedFriendMessageStatusDTO^> ^tempList = ref new Platform::Array<ManagedFriendMessageStatusDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::FriendMessageStatusDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedFriendMessageStatusDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}

	ManagedApiStatus ^DataConvertionUtility::ToManagedApiStatus(imsdk::ApiStatus &apiStatus)
	{
		if (&apiStatus)
		{
			return ref new ManagedApiStatus(ToManagedString(apiStatus.getPacketId()), apiStatus.getErrorCode());
		}
		else
		{
			return nullptr;
		}
	}


	ManagedFriendInformation ^DataConvertionUtility::ToManagedFriendInformation(imsdk::FriendInformation &friendInfo)
	{
		if (&friendInfo)
		{
			return ref new ManagedFriendInformation(friendInfo);
		}
		else
		{
			return nullptr;
		}
	}

	set<long long> DataConvertionUtility::ToNativeCollectionSet(const Platform::Array<long long> ^list)
	{
		int count = list->Length;
		set<long long> vector;

		for (int i = 0; i < count; i++)
		{
			vector.insert(list[i]);
		}
		return vector;
	}

	vector<long long> DataConvertionUtility::ToNativeCollection(const Platform::Array<long long> ^list)
	{
		int count = list->Length;
		vector<long long> vector;

		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]);
		}
		return vector;
	}

	Platform::Array<long long>^ DataConvertionUtility::ToManagedCollection(const vector<long long> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<long long> ^tempList = ref new Platform::Array<long long>(count);
			for (int i = 0; i < count; i++)
			{
				tempList->set(i, vector[i]);
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}



	vector<imsdk::MemberDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedMemberDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::MemberDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedMemberDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::MemberDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedMemberDTO^> ^tempList = ref new Platform::Array<ManagedMemberDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::MemberDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedMemberDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}



	ManagedGroupInformation ^DataConvertionUtility::ToManagedGroupInformation(imsdk::GroupInformation &groupInfo)
	{
		if (&groupInfo)
		{
			return ref new ManagedGroupInformation(groupInfo);
		}
		else
		{
			return nullptr;
		}
	}

	vector<imsdk::GroupInformation> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedGroupInformation^> ^list)
	{
		int count = list->Length;
		vector<imsdk::GroupInformation> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedGroupInformation^>^ DataConvertionUtility::ToManagedCollection(vector<imsdk::GroupInformation> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedGroupInformation^> ^tempList = ref new Platform::Array<ManagedGroupInformation^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::GroupInformation tempDTO = vector[i];
				tempList->set(i, ref new ManagedGroupInformation(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	Platform::Array<ManagedGroupInformation^>^ DataConvertionUtility::ToManagedCollection(vector<shared_ptr<imsdk::GroupInformation>> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedGroupInformation^> ^tempList = ref new Platform::Array<ManagedGroupInformation^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::GroupInformation tempDTO = *vector[i];
				tempList->set(i, ref new ManagedGroupInformation(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	vector<imsdk::GroupActivityDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedGroupActivityDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::GroupActivityDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedGroupActivityDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::GroupActivityDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedGroupActivityDTO^> ^tempList = ref new Platform::Array<ManagedGroupActivityDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::GroupActivityDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedGroupActivityDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	vector<imsdk::GroupDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedGroupDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::GroupDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedGroupDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::GroupDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedGroupDTO^> ^tempList = ref new Platform::Array<ManagedGroupDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::GroupDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedGroupDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	ManagedPacketTimeID ^DataConvertionUtility::ToManagedPacketTimeID(imsdk::PacketTimeId &packetTimeId)
	{
		if (&packetTimeId)
		{
			return ref new ManagedPacketTimeID(packetTimeId);
		}
		else
		{
			return nullptr;
		}
	}

	vector<imsdk::PacketTimeId> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedPacketTimeID^> ^list)
	{
		int count = list->Length;
		vector<imsdk::PacketTimeId> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedPacketTimeID^>^ DataConvertionUtility::ToManagedCollection(vector<imsdk::PacketTimeId> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedPacketTimeID^> ^tempList = ref new Platform::Array<ManagedPacketTimeID^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::PacketTimeId tempDTO = vector[i];
				tempList->set(i, ref new ManagedPacketTimeID(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	vector<imsdk::RoomDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedRoomDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::RoomDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedRoomDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::RoomDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedRoomDTO^> ^tempList = ref new Platform::Array<ManagedRoomDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::RoomDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedRoomDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	vector<imsdk::PublicChatMemberDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedPublicChatMemberDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::PublicChatMemberDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedPublicChatMemberDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::PublicChatMemberDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedPublicChatMemberDTO^> ^tempList = ref new Platform::Array<ManagedPublicChatMemberDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::PublicChatMemberDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedPublicChatMemberDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}


	ManagedDataCounter ^DataConvertionUtility::ToManagedDataCounter(const imsdk::DataCounter &dataCounter)
	{
		if (&dataCounter)
		{
			return ref new ManagedDataCounter(dataCounter);
		}
		else
		{
			return nullptr;
		}
	}


	imsdk::ConversationType DataConvertionUtility::ToNativeConversationType(int conversationType)
	{
		switch (conversationType)
		{
		case 2:
			return imsdk::ConversationType::UNSEEN;
			break;
		case 3:
			return imsdk::ConversationType::FRIEND_ID;
			break;
		case 4:
			return imsdk::ConversationType::GROUP_ID;
			break;
		case 1:
		default:
			return imsdk::ConversationType::ALL;
			break;
		}
	}


	vector<imsdk::ConversationDTO> DataConvertionUtility::ToNativeCollection(const Platform::Array<ManagedConversationDTO^> ^list)
	{
		int count = list->Length;
		vector<imsdk::ConversationDTO> vector;
		for (int i = 0; i < count; i++)
		{
			vector.push_back(list[i]->ToNativeInstance());
		}
		return vector;
	}

	Platform::Array<ManagedConversationDTO^>^ DataConvertionUtility::ToManagedCollection(const vector<imsdk::ConversationDTO> &vector)
	{
		if (&vector)
		{
			int count = vector.size();
			Platform::Array<ManagedConversationDTO^> ^tempList = ref new Platform::Array<ManagedConversationDTO^>(count);
			for (int i = 0; i < count; i++)
			{
				imsdk::ConversationDTO tempDTO = vector[i];
				tempList->set(i, ref new ManagedConversationDTO(tempDTO));
			}
			return tempList;
		}
		else
		{
			return nullptr;
		}
	}

}
