#include "stdafx.h"
#include "WinTemp.h"

WinTemp::WinTemp()
{
	DWORD dwRetVal = GetTempPath(MAX_PATH, this->lpTempPathBuffer);

	if( (dwRetVal == 0) || (dwRetVal > MAX_PATH) )
	{
		this->LastError = "GetTempPath() failed.";
		return;
	}
}

std::string WinTemp::GetLastError()
{
	return this->LastError;
}

TCHAR* WinTemp::GetTempFile()
{
	return this->szTempFileName;
}

void WinTemp::CreateTempFile()
{
	UINT uRetVal = GetTempFileName(this->lpTempPathBuffer, "", 0, this->szTempFileName); 

	if(uRetVal == 0)
	{
		this->LastError = "GetTempFileName() failed.";
		return;
	}
}

void WinTemp::DeleteTempFile()
{
	DeleteFile(this->szTempFileName);
}

WinTemp::~WinTemp()
{
	
}