#include "stdafx.h"
#include "Pastebin.h"

Pastebin::Pastebin()
{
	this->m_Address	= "www.pastebin.com";
	this->m_Port		= 80;
	this->m_Target = "/api/api_post.php";
	this->m_ContentType = "application/x-www-form-urlencoded; charset=utf-8";

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
	this->m_PostData += upload_text.str();

	std::string link = HttpClient::Upload();

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
	std::string link = HttpClient::Upload();

	return link;
}

std::string Pastebin::ParseResult(char *Buffer)
{
	return Buffer;
}

Pastebin::~Pastebin()
{

}