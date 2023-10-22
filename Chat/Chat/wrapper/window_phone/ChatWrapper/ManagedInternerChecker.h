#pragma once
#include "InternetChecker.h"

namespace ChatWrapper
{
	public ref class ManagedInternerChecker sealed
	{
	public:
		ManagedInternerChecker(Platform::String ^ipListFilePath);
		bool checkInternetConnection();
	};
}

