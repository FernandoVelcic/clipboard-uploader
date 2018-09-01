#pragma once

class Clipboard
{
private:
	char *m_szText;
	char m_szFileName[MAX_PATH];

public:
	Clipboard();
	~Clipboard();

	void Open();
	void Close();
	void Clear();

	unsigned int GetFormat();

	char* GetText();
	void SetText(const char *szText);

	char* GetFileDirectory();

	void SaveImage(char *szFileName);
};