#pragma once

enum ClipboardType {
	CT_TEXT,
	CT_DIB,
	CT_HDROP
};

class Clipboard
{
private:
	char m_szFileName[255];

public:
	unsigned int GetFormat();

	std::string GetText();
	void SetText(const char *szText);

	std::string GetFileDirectory();

	void SaveImage(char *szFileName);
};