#include "stdafx.h"
#include "Pastebin.h"
#include "Socket.h"

Pastebin::Pastebin()
{
	this->m_Address	= "www.pastebin.com";
	this->m_Port		= 80;

	this->m_Header = "POST /api/api_post.php HTTP/1.1\r\n";
	this->m_Header += "Host: " + std::string(this->m_Address) + std::string("\r\n");
	this->m_Header += "Content-type: application/x-www-form-urlencoded; charset=utf-8\r\n";

	this->m_PostData = "api_dev_key=" + std::string(PASTEBIN_API_KEY);
	this->m_PostData += "&api_option=paste&api_paste_private=1";
	//&api_user_key=
}

std::string Pastebin::Upload(char *lpszTitle, char *lpszContent)
{
	std::stringstream upload_text;

	upload_text << "&api_paste_name=" << lpszTitle;
	upload_text << "&api_paste_code=" << UrlEncode(lpszContent);

	/*
	/	Final m_Packet assembling.
	*/
	this->m_Packet << this->m_Header;
	this->m_Packet << "Content-length: " << m_PostData.size()+upload_text.str().size() << "\r\n\r\n";
	this->m_Packet << this->m_PostData;
	this->m_Packet << upload_text.str();

	std::string link = HttpConnection::Upload();

	m_Packet.clear();

	return link;
}

std::string Pastebin::Upload(char *szFileName, char *lpszTitle, unsigned char Type)
{
	std::stringstream upload_text;

	upload_text << "&api_paste_name=" << lpszTitle;
	upload_text << "&api_paste_code=" << UrlEncode( LoadFileFromDisk(szFileName) );
	
	upload_text << "&api_paste_format=";

	switch(Type)
	{
	case FILE_CPP:
		upload_text << "cpp";
		break;
	case FILE_OBJC:
		upload_text << "objc";
		break;
	case FILE_ASM:
		upload_text << "asm";
		break;
	case FILE_PHP:
		upload_text << "php";
		break;
	case FILE_CSHARP:
		upload_text << "csharp";
		break;
	case FILE_JAVA:
		upload_text << "java";
		break;
	case FILE_VB:
		upload_text << "vb";
		break;
	case FILE_CSS:
		upload_text << "css";
		break;
	case FILE_HTML:
		upload_text << "html5";
		break;
	case FILE_JS:
		upload_text << "javascript";
		break;

	case FILE_TEXT:
		upload_text << "none";
		break;
	case FILE_INI:
		upload_text << "ini";
		break;
	case FILE_XML:
		upload_text << "xml";
		break;
	case FILE_LUA:
		upload_text << "lua";
		break;
	}

	/*
	/	Final m_Packet assembling.
	*/
	this->m_Packet << this->m_Header;
	this->m_Packet << "Content-length: " << m_PostData.size()+upload_text.str().size() << "\r\n\r\n";
	this->m_Packet << this->m_PostData;
	this->m_Packet << upload_text.str();

	std::string link = HttpConnection::Upload();

	m_Packet.clear();

	return link;
}

std::string Pastebin::ParseResult(char *Buffer)
{
	std::string link = Buffer;
	size_t pos; size_t pos2;

	pos = link.find("1d\r\n") + strlen("1d\r\n");
	pos2 = link.find("\r\n");

	link = link.substr(pos, pos2-pos);

	return link;
}

Pastebin::~Pastebin()
{

}