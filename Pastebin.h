#pragma once
#include "HttpConnection.h"

class Pastebin : private HttpConnection
{
public:
	Pastebin();
	~Pastebin();

	std::string Upload(char *lpszTitle, char *lpszContent);
	std::string Upload(char *szFileName, char *lpszTitle, unsigned char Type);

	std::string ParseResult(char *Buffer);
};