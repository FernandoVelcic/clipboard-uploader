#include "stdafx.h"
#include "Imageshack.h"

Imageshack::Imageshack()
{
	this->m_Address	= "www.imageshack.us";
	this->m_Port		= 80;
	this->m_Target = "/upload_api.php";
	this->m_ContentType = "Content-type: multipart/form-data, boundary=BO--UN--DA--RY----FI--LE\r\n";

	this->m_PostData = "--BO--UN--DA--RY----FI--LE\r\n";
	this->m_PostData += "Content-Disposition: form-data; name=\"key\"\r\n\r\n" + std::string(IMAGESHACK_API_KEY) + std::string("\r\n");
	this->m_PostData += "--BO--UN--DA--RY----FI--LE\r\n";
	this->m_PostData += "Content-Disposition: form-data; name=\"uploadtype\"\r\n\r\n";
	this->m_PostData += "on\r\n";
	this->m_PostData += "--BO--UN--DA--RY----FI--LE\r\n";
}

std::string Imageshack::Upload(char *szFileName, unsigned char Type)
{
	std::stringstream file_upload;

	file_upload << "Content-Disposition: form-data; name=\"fileupload\"; ";

	switch(Type)
	{
	case FILE_JPEG:
		file_upload << "filename=\"upload.jpg\"\r\n";
		file_upload << "Content-Type: image/jpeg\r\n\r\n";
		break;

	case FILE_PNG:
		file_upload << "filename=\"upload.png\"\r\n";
		file_upload << "Content-Type: image/png\r\n\r\n";
		break;

	case FILE_GIF:
		file_upload << "filename=\"upload.gif\"\r\n";
		file_upload << "Content-Type: image/gif\r\n\r\n";
		break;

	case FILE_BMP:
		file_upload << "filename=\"upload.bmp\"\r\n";
		file_upload << "Content-Type: image/bmp\r\n\r\n";
		break;
	}
	
	/*
	/	Read image from disk.
	*/
	file_upload << LoadFileFromDisk(szFileName);

	file_upload << "\r\n";
	file_upload << "--BO--UN--DA--RY----FI--LE--\r\n";

	/*
	/	Final m_Packet assembling.
	*/
	this->m_PostData += file_upload.str();

	std::string link = HttpClient::Upload();

	return link;
}

std::string Imageshack::ParseResult(char *Buffer)
{
	std::string link = Buffer;
	size_t pos, pos2;

	pos = link.find("<image_link>") + strlen("<image_link>");
	pos2 = link.find("</image_link>");

	link = link.substr(pos, pos2-pos);

	return link;
}

Imageshack::~Imageshack()
{

}
