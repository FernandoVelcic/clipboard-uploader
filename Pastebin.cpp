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

std::string Pastebin::Upload(std::string title, std::string content)
{
	std::stringstream upload_text;

	upload_text << "&api_paste_name=" << title;
	upload_text << "&api_paste_code=" << UrlEncode(content);

	/*
	/	Final m_Packet assembling.
	*/
	this->m_PostData += upload_text.str();

	std::string link = HttpClient::Upload();

	return link;
}

std::string Pastebin::Upload(std::string fileName)
{
	return this->Upload(fileName, LoadFileFromDisk(fileName));
}

std::string Pastebin::ParseResult(char *Buffer)
{
	return Buffer;
}

Pastebin::~Pastebin()
{

}