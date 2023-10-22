#include "ManagedDataEncryption.h"
#include "DataEncryption.h"
#include "DataConvertionUtility.h"


namespace ChatWrapper
{
	ManagedDataEncryption::ManagedDataEncryption()
	{
	}

	Platform::String ^ManagedDataEncryption::getSessionlessKey(Platform::String ^ipAddress, long long ringId)
	{
		return DataConvertionUtility::ToManagedString(ipvsdk::security::DataEncryption::getSessionlessKey(DataConvertionUtility::ToNativeString(ipAddress), ringId));
	}

	Platform::Array<uint8> ^ManagedDataEncryption::encryptMessage(const Platform::Array<uint8> ^data, const Platform::Array<uint8> ^key, int startIndex)
	{
		imsdk::ByteArray dataNative(data->Data, data->Length);
		imsdk::ByteArray keyNative(key->Data, key->Length);
		imsdk::ByteArray encryptedNative = ipvsdk::security::DataEncryption::encryptMessage(dataNative, keyNative, startIndex);
		return ref new  Platform::Array<uint8>(encryptedNative.getDataPtr(), encryptedNative.size());
	}

	Platform::Array<uint8> ^ManagedDataEncryption::decryptMessage(const Platform::Array<uint8> ^data, const Platform::Array<uint8> ^key, int startIndex)
	{
		imsdk::ByteArray dataNative(data->Data, data->Length);
		imsdk::ByteArray keyNative(key->Data, key->Length);
		imsdk::ByteArray decryptedNative = ipvsdk::security::DataEncryption::decryptMessage(dataNative, keyNative, startIndex);
		return ref new  Platform::Array<uint8>(decryptedNative.getDataPtr(), decryptedNative.size());
	}
}
