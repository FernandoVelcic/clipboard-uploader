#pragma once

class HttpConnection
{
protected:
	std::string m_Header;
	std::string m_PostData;
	std::stringstream m_Packet;

	char *m_Address;
	unsigned short m_Port;

protected:
	HttpConnection();
	~HttpConnection();

	std::string Upload();
	
	std::string UrlEncode(const std::string & sSrc);
	std::string UrlDecode(const std::string & sSrc);

	std::string LoadFileFromDisk(char *szFileName);

	virtual std::string ParseResult(char *Buffer) = 0;
};