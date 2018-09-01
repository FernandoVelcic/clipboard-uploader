#pragma once

class WinTemp
{
private:
	TCHAR lpTempPathBuffer[MAX_PATH];
	TCHAR szTempFileName[MAX_PATH];

	std::string LastError;
public:
	WinTemp();
	~WinTemp();

	std::string GetLastError();
	TCHAR* GetTempFile();
	void CreateTempFile();
	void DeleteTempFile();
};