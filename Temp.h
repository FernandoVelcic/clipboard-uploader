#pragma once
class CTemp
{
private:
	char FileName[L_tmpnam];

public:
	CTemp(void);
	~CTemp(void);

	void Create(void);
	void Destroy(void);

	char* GetFileName(void);
};