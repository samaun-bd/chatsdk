#include "ManagedRoomDTO.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedRoomDTO::ManagedRoomDTO()
	{
		this->roomDTO = new imsdk::RoomDTO();
	}

	ManagedRoomDTO::ManagedRoomDTO(Platform::String ^roomId, Platform::String ^roomFullName, Platform::String ^roomPictureUrl)
	{
		this->roomDTO = new imsdk::RoomDTO(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeString(roomFullName), DataConvertionUtility::ToNativeString(roomPictureUrl));
	}

	ManagedRoomDTO::ManagedRoomDTO(imsdk::RoomDTO &roomDTO)
	{
		this->roomDTO = new imsdk::RoomDTO();
		*this->roomDTO = roomDTO;
	}

	ManagedRoomDTO::~ManagedRoomDTO()
	{
	}

	//ManagedRoomDTO::!ManagedRoomDTO()
	//{
	//	delete roomDTO;
	//}

	void ManagedRoomDTO::RoomImageUrl::set(Platform::String ^roomPictureUrl)
	{
		this->roomDTO->setRoomPictureUrl(DataConvertionUtility::ToNativeString(roomPictureUrl));
	}

	Platform::String ^ManagedRoomDTO::RoomImageUrl::get()
	{
		return DataConvertionUtility::ToManagedString(this->roomDTO->getRoomPictureUrl());
	}

	void ManagedRoomDTO::RoomName::set(Platform::String ^roomFullName)
	{
		this->roomDTO->setRoomFullName(DataConvertionUtility::ToNativeString(roomFullName));
	}

	Platform::String ^ManagedRoomDTO::RoomName::get()
	{
		return DataConvertionUtility::ToManagedString(this->roomDTO->getRoomFullName());
	}

	void ManagedRoomDTO::RoomID::set(Platform::String ^roomId)
	{
		this->roomDTO->setRoomId(DataConvertionUtility::ToNativeString(roomId));
	}

	Platform::String ^ManagedRoomDTO::RoomID::get()
	{
		return DataConvertionUtility::ToManagedString(this->roomDTO->getRoomId());
	}

	void ManagedRoomDTO::NumberOfMember::set(int numberOfMember)
	{
		this->roomDTO->setNumberOfMember(numberOfMember);
	}

	int ManagedRoomDTO::NumberOfMember::get()
	{
		return this->roomDTO->getNumberOfMember();
	}

	void ManagedRoomDTO::RoomMessageList::set(const Platform::Array<ManagedMessageDTO^>^ messageList)
	{
		this->roomDTO->setRoomMessageList(DataConvertionUtility::ToNativeCollection(messageList));
	}

	Platform::Array<ManagedMessageDTO^>^ ManagedRoomDTO::RoomMessageList::get()
	{
		return DataConvertionUtility::ToManagedCollection(this->roomDTO->getRoomMessageList());
	}

	Platform::String^ ManagedRoomDTO::ToDebugString()
	{
		return "RoomDTO [RoomID = " + RoomID + ", RoomName = " + RoomName + ", RoomImageUrl = " + RoomImageUrl + ", NumberOfMember = " + NumberOfMember + "]";
	}

	imsdk::RoomDTO ManagedRoomDTO::ToNativeInstance()
	{
		return *roomDTO;
	}
}
