#include "stdafx.h"
#include "Clipboard.h"
#include "third_party/clip/clip.h"

#ifdef _MSC_VER
#include <Windows.h>
#include <atlimage.h>
#include <Gdiplusimaging.h>
#endif


std::string Clipboard::GetText()
{
	std::string text;
	clip::get_text(text);

	return text;
}

void Clipboard::SetText(const char *szText)
{
	clip::set_text(szText);
}

void Clipboard::SaveImage(char *szFileName)
{
#ifdef _MSC_VER
	OpenClipboard(NULL);
	HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	CloseClipboard();

	CImage cImage;

	cImage.Attach(hBitmap);
	cImage.Save(szFileName, Gdiplus::ImageFormatJPEG);
#endif
}

std::string Clipboard::GetFileDirectory()
{
	if (clip::has(clip::file_format())) {
		std::string file;
		clip::get_file(file);
		return file;
	}

	return NULL;
}

unsigned int Clipboard::GetFormat()
{
	if (clip::has(clip::file_format()))
		return CT_HDROP;
	else if (clip::has(clip::text_format()))
		return CT_TEXT;
	else if (clip::has(clip::image_format()))
		return CT_DIB;

	return 0;
}