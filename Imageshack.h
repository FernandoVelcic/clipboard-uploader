#pragma once
#include "HttpConnection.h"

class Imageshack : private HttpConnection
{
public:
	Imageshack();
	~Imageshack();

	std::string Upload(char *szFileName, unsigned char Type);
	std::string ParseResult(char *Buffer);
};