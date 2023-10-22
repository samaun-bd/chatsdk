#include "ManagedDataCounter.h"

namespace ChatWrapper
{
	ManagedDataCounter::ManagedDataCounter()
	{
		this->dataCounter = new imsdk::DataCounter(0, 0);
	}

	ManagedDataCounter::ManagedDataCounter(long long dataSent, long long dataReceived)
	{
		this->dataCounter = new imsdk::DataCounter(dataSent, dataReceived);
	}

	ManagedDataCounter::ManagedDataCounter(const imsdk::DataCounter &dataCounter)
	{
		this->dataCounter = new imsdk::DataCounter(dataCounter.getDataSent(), dataCounter.getDataReceived());
	}

	ManagedDataCounter::~ManagedDataCounter()
	{
	}

	void ManagedDataCounter::DataSent::set(long long dataSent)
	{
		this->dataCounter->setDataSent(dataSent);
	}

	long long ManagedDataCounter::DataSent::get()
	{
		return dataCounter->getDataSent();
	}

	void ManagedDataCounter::DataReceived::set(long long dataSent)
	{
		this->dataCounter->setDataReceived(dataSent);
	}

	long long ManagedDataCounter::DataReceived::get()
	{
		return dataCounter->getDataReceived();
	}

	Platform::String^ ManagedDataCounter::ToString()
	{
		return "DataCounter [DataSent = " + DataSent + ", DataReceived = " + DataReceived + "]";
	}

	imsdk::DataCounter ManagedDataCounter::ToNativeInstance()
	{
		return *dataCounter;
	}

}
