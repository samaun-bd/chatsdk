#pragma once


namespace ChatWrapper
{
	public ref class ManagedDataEncryption sealed
	{
	public:
		ManagedDataEncryption();
		Platform::String ^getSessionlessKey(Platform::String ^ipAddress, long long ringId);
		Platform::Array<uint8> ^encryptMessage(const Platform::Array<uint8> ^data, const Platform::Array<uint8> ^key, int startIndex);
		Platform::Array<uint8> ^decryptMessage(const Platform::Array<uint8> ^data, const Platform::Array<uint8> ^key, int startIndex);
	};
}

