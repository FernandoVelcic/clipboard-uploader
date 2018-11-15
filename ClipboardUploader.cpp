#include "stdafx.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <boost/log/expressions.hpp>

#include "Imageshack.h"
#include "Pastebin.h"

#include "Temp.h"
#include "Clipboard.h"
#include "params.h"

params p;


void App()
{
	Clipboard ClipBoard;

	Imageshack ImageShack;
	Pastebin PasteBin;

	CTemp Temp;

	std::string link;

	switch( ClipBoard.GetFormat() )
	{
	case CT_TEXT:
		link = PasteBin.Upload("unknown", ClipBoard.GetText());
		ClipBoard.SetText(link.c_str());
		break;
	
	case CT_DIB:
		Temp.Create();

		ClipBoard.SaveImage(Temp.GetFileName());
		link = ImageShack.Upload(Temp.GetFileName(), FILE_JPEG);

		ClipBoard.SetText(link.c_str());

		Temp.Destroy();
		break;

	case CT_HDROP:
		std::string fileName = ClipBoard.GetFileDirectory();

		int pos = fileName.find_last_of(".");
		std::string fileExtension = fileName.substr(pos+1);
		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

		//Images
		if (fileExtension == "jpg" || fileExtension == "jpeg")
			link = ImageShack.Upload(fileName, FILE_JPEG);
		else if(fileExtension == "png")
			link = ImageShack.Upload(fileName, FILE_PNG);
		else if(fileExtension == "gif")
			link = ImageShack.Upload(fileName, FILE_GIF);
		else if(fileExtension == "bmp")
			link = ImageShack.Upload(fileName, FILE_BMP);
		
		//Text||script
		else if(fileExtension == "txt")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "ini")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "xml")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "lua")
			link = PasteBin.Upload(fileName);

		//Languages
		else if(fileExtension == "c" || fileExtension == "cpp")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "h" || fileExtension == "hpp")
			link = PasteBin.Upload(fileName);

		else if(fileExtension == "objc")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "asm")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "cs")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "java")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "php")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "vb")
			link = PasteBin.Upload(fileName);

		else if(fileExtension == "css")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "htm" || fileExtension == "html")
			link = PasteBin.Upload(fileName);
		else if(fileExtension == "js")
			link = PasteBin.Upload(fileName);

		else
		{
			//TODO
			//link = SendSpace.Upload(fileName);
			return;
		}

		ClipBoard.SetText(link.c_str());
		break;
	}
}


int main(int argc, char* argv[])
{
	//Command line parameters
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")

		("verbose,v", boost::program_options::bool_switch(&p.verboseMode), "set log level to trace");

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		return 1;
	}

	//Logs
	boost::log::core::get()->set_filter
	(
		boost::log::trivial::severity >= ((p.verboseMode) ? boost::log::trivial::trace : boost::log::trivial::debug)
	);

	App();

	return 0;
}
