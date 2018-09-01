#include "stdafx.h"

#include "Imageshack.h"
#include "Pastebin.h"

#include "Temp.h"
#include "Clipboard.h"

Imageshack ImageShack;
Pastebin PasteBin;

CTemp Temp;
Clipboard ClipBoard;

void App()
{
	std::string link;

	switch( ClipBoard.GetFormat() )
	{
	case CF_TEXT:
		link = PasteBin.Upload("unknown", ClipBoard.GetText());
		ClipBoard.SetText(link.c_str());
		break;
	case CF_UNICODETEXT:
		break;
	
	case CF_DIB:
		Temp.Create();

		ClipBoard.SaveImage(Temp.GetFileName());
		link = ImageShack.Upload(Temp.GetFileName(), FILE_JPEG);

		ClipBoard.SetText(link.c_str());

		Temp.Destroy();
		break;

	case CF_HDROP:
		char *szFileName = ClipBoard.GetFileDirectory();
		std::string FileName = szFileName;

		int pos = FileName.find_last_of(".");
		std::string FileExtension = FileName.substr(pos+1);
		std::transform(FileExtension.begin(), FileExtension.end(), FileExtension.begin(), ::tolower);

		//Images
		if (FileExtension == "jpg" || FileExtension == "jpeg")
			link = ImageShack.Upload(szFileName, FILE_JPEG);
		else if(FileExtension == "png")
			link = ImageShack.Upload(szFileName, FILE_PNG);
		else if(FileExtension == "gif")
			link = ImageShack.Upload(szFileName, FILE_GIF);
		else if(FileExtension == "bmp")
			link = ImageShack.Upload(szFileName, FILE_BMP);
		
		//Text||script
		else if(FileExtension == "txt")
			link = PasteBin.Upload(szFileName, "unknown", FILE_TEXT);
		else if(FileExtension == "ini")
			link = PasteBin.Upload(szFileName, "unknown", FILE_INI);
		else if(FileExtension == "xml")
			link = PasteBin.Upload(szFileName, "unknown", FILE_XML);
		else if(FileExtension == "lua")
			link = PasteBin.Upload(szFileName, "unknown", FILE_LUA);

		//Languages
		else if(FileExtension == "c" || FileExtension == "cpp")
			link = PasteBin.Upload(szFileName, "unknown", FILE_CPP);
		else if(FileExtension == "h" || FileExtension == "hpp")
			link = PasteBin.Upload(szFileName, "unknown", FILE_CPP);

		else if(FileExtension == "objc")
			link = PasteBin.Upload(szFileName, "unknown", FILE_OBJC);
		else if(FileExtension == "asm")
			link = PasteBin.Upload(szFileName, "unknown", FILE_ASM);
		else if(FileExtension == "cs")
			link = PasteBin.Upload(szFileName, "unknown", FILE_CSHARP);
		else if(FileExtension == "java")
			link = PasteBin.Upload(szFileName, "unknown", FILE_JAVA);
		else if(FileExtension == "php")
			link = PasteBin.Upload(szFileName, "unknown", FILE_PHP);
		else if(FileExtension == "vb")
			link = PasteBin.Upload(szFileName, "unknown", FILE_VB);

		else if(FileExtension == "css")
			link = PasteBin.Upload(szFileName, "unknown", FILE_CSS);
		else if(FileExtension == "htm" || FileExtension == "html")
			link = PasteBin.Upload(szFileName, "unknown", FILE_HTML);
		else if(FileExtension == "js")
			link = PasteBin.Upload(szFileName, "unknown", FILE_JS);

		else
		{
			//TODO
			//link = SendSpace.Upload(szFileName);
			return;
		}

		ClipBoard.SetText(link.c_str());
		break;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	App();

	return 0;
}
