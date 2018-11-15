#pragma once
#include "HttpClient.h"

class Imageshack : private HttpClient
{
public:
	Imageshack();
	~Imageshack();

	std::string Upload(std::string fileName, unsigned char Type);
	std::string ParseResult(char *Buffer);
};