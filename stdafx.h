#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

///////////////////////////////////////////////////////////////////////
#pragma comment( lib, "ws2_32.lib" )
#include <winsock2.h>
#include <Windows.h>

///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////
#include <atlimage.h>
#include <Gdiplusimaging.h>

///////////////////////////////////////////////////////////////////////
enum FileFormats
{
	FILE_JPEG = 1,
	FILE_PNG = 2,
	FILE_GIF = 3,
	FILE_BMP = 4,

	FILE_OBJC = 5,
	FILE_CPP = 6,
	FILE_ASM = 7,
	FILE_PHP = 8,
	FILE_CSHARP = 9,
	FILE_JAVA = 10,
	FILE_CSS = 11,
	FILE_HTML = 12,
	FILE_JS = 13,
	FILE_VB = 14,

	FILE_TEXT = 15,
	FILE_INI = 16,
	FILE_XML = 17,
	FILE_LUA = 18
};

///////////////////////////////////////////////////////////////////////
#define IMAGESHACK_API_KEY	""
#define PASTEBIN_API_KEY	""