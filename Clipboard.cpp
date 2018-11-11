#include "stdafx.h"
#include "Clipboard.h"
#include "third_party/clip/clip.h"


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
	OpenClipboard(NULL);
	HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	CloseClipboard();

	CImage cImage;

	cImage.Attach(hBitmap);
	cImage.Save(szFileName, Gdiplus::ImageFormatJPEG);
}

char* Clipboard::GetFileDirectory()
{
	OpenClipboard(NULL);
	HANDLE hData = GetClipboardData(CF_HDROP);
	CloseClipboard();
	
	if( DragQueryFile((HDROP)hData, 0xFFFFFFFF, NULL, 0) == 1 )
	{
		DragQueryFile((HDROP)hData, 0, m_szFileName, MAX_PATH);

		return m_szFileName;
	}

	return NULL;
}

unsigned int Clipboard::GetFormat()
{
	OpenClipboard(NULL);

	if( IsClipboardFormatAvailable(CF_TEXT) )
		return CF_TEXT;
	else if( IsClipboardFormatAvailable(CF_UNICODETEXT) )
		return CF_UNICODETEXT;
	else if( IsClipboardFormatAvailable(CF_DIB) )
		return CF_DIB;
	else if( IsClipboardFormatAvailable(CF_HDROP) )
		return CF_HDROP;

	CloseClipboard();

	return 0;
}