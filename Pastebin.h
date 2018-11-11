#pragma once
#include "HttpClient.h"

class Pastebin : private HttpClient
{
public:
	Pastebin();
	~Pastebin();

	std::string Upload(char *lpszTitle, std::string content);
	std::string Upload(char *szFileName, char *lpszTitle, unsigned char Type);

	std::string ParseResult(char *Buffer);
};