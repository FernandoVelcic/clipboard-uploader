#pragma once

class HttpClient
{
protected:
	std::string m_PostData;
	std::string m_ContentType;
	std::string m_Target;

	std::string m_Address;
	unsigned short m_Port;

protected:
	HttpClient();
	~HttpClient();

	std::string Upload();
	
	std::string UrlEncode(const std::string & sSrc);
	std::string UrlDecode(const std::string & sSrc);

	std::string LoadFileFromDisk(std::string fileName);

	virtual std::string ParseResult(char *Buffer) = 0;
};