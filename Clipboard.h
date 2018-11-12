#pragma once

#ifndef WIN32
#define MAX_PATH 255
#define CF_TEXT 0
#define CF_UNICODETEXT 1
#define CF_DIB 2
#define CF_HDROP 3
#endif

class Clipboard
{
private:
	char m_szFileName[MAX_PATH];

public:
	unsigned int GetFormat();

	std::string GetText();
	void SetText(const char *szText);

	char* GetFileDirectory();

	void SaveImage(char *szFileName);
};