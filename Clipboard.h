#pragma once

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