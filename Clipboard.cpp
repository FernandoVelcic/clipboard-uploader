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

char* Clipboard::GetFileDirectory()
{
#ifdef _MSC_VER
	OpenClipboard(NULL);
	HANDLE hData = GetClipboardData(CF_HDROP);
	CloseClipboard();
	
	if( DragQueryFile((HDROP)hData, 0xFFFFFFFF, NULL, 0) == 1 )
	{
		DragQueryFile((HDROP)hData, 0, m_szFileName, MAX_PATH);

		return m_szFileName;
	}

#endif

	return NULL;
}

unsigned int Clipboard::GetFormat()
{
#ifdef _MSC_VER
	OpenClipboard(NULL);

	if( IsClipboardFormatAvailable(CF_HDROP) )
		return CT_HDROP;

	CloseClipboard();
#endif

	if (clip::has(clip::text_format()))
		return CT_TEXT;
	else if (clip::has(clip::image_format()))
		return CT_DIB;

	return 0;
}