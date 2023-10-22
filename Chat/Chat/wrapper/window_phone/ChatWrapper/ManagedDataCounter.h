#pragma once
#include "DataCounter.h"

namespace ChatWrapper
{
	public ref class ManagedDataCounter sealed
	{
	public:
		ManagedDataCounter();
		ManagedDataCounter(long long dataSent, long long dataReceived);
		virtual ~ManagedDataCounter();

		property long long DataSent { long long get(); void set(long long value); }
		property long long DataReceived { long long get(); void set(long long value); }

		virtual Platform::String^ ToString() override;

	internal:
		ManagedDataCounter(const imsdk::DataCounter &dataCounter);
		imsdk::DataCounter ToNativeInstance();

	private:
		imsdk::DataCounter *dataCounter;
	};
}

