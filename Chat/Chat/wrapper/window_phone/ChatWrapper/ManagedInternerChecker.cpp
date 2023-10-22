#include "ManagedInternerChecker.h"
#include "DataConvertionUtility.h"

namespace ChatWrapper
{
	ManagedInternerChecker::ManagedInternerChecker(Platform::String ^ipListFilePath)
	{
		internetchecker::InternetChecker::getInstance().setIpListFilePath(DataConvertionUtility::ToNativeString(ipListFilePath));
	}

	bool ManagedInternerChecker::checkInternetConnection()
	{
		return internetchecker::InternetChecker::getInstance().checkInternetConnection();
	}
}