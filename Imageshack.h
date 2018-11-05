#pragma once
#include "HttpClient.h"

class Imageshack : private HttpClient
{
public:
	Imageshack();
	~Imageshack();

	std::string Upload(char *szFileName, unsigned char Type);
	std::string ParseResult(char *Buffer);
};