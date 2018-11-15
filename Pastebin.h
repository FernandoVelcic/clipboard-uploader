#pragma once
#include "HttpClient.h"

class Pastebin : private HttpClient
{
public:
	Pastebin();
	~Pastebin();

	std::string Upload(std::string title, std::string content);
	std::string Upload(std::string fileName);

	std::string ParseResult(char *Buffer);
};