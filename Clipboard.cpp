#include "stdafx.h"
#include "Clipboard.h"

Clipboard::Clipboard()
{
	
}

Clipboard::~Clipboard()
{

}

void Clipboard::Open()
{
	OpenClipboard(NULL);
}

void Clipboard::Close()
{
	CloseClipboard();
}

void Clipboard::Clear()
{
	EmptyClipboard();
}

char* Clipboard::GetText()
{
	Open();
	HANDLE hClipboard = GetClipboardData(CF_TEXT);
	Close();

	m_szText = (char*)hClipboard;

	return m_szText;
}

void Clipboard::SetText(const char *szText)
{
	Open();
	Clear();

	HGLOBAL hMem = GlobalAlloc(GMEM_DDESHARE, strlen(szText)+1);
	char *buffer;
   
	buffer = (char*)GlobalLock(hMem);
	strcpy(buffer, szText);
	GlobalUnlock(hMem);

	SetClipboardData(CF_TEXT, hMem);
	Close();
}

void Clipboard::SaveImage(char *szFileName)
{
	Open();
	HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	Close();

	CImage cImage;

	cImage.Attach(hBitmap);
	cImage.Save(szFileName, Gdiplus::ImageFormatJPEG);
}

char* Clipboard::GetFileDirectory()
{
	Open();
	HANDLE hData = GetClipboardData(CF_HDROP);
	Close();
	
	if( DragQueryFile((HDROP)hData, 0xFFFFFFFF, NULL, 0) == 1 )
	{
		DragQueryFile((HDROP)hData, 0, m_szFileName, MAX_PATH);

		return m_szFileName;
	}

	return NULL;
}

unsigned int Clipboard::GetFormat()
{
	Open();

	if( IsClipboardFormatAvailable(CF_TEXT) )
		return CF_TEXT;
	else if( IsClipboardFormatAvailable(CF_UNICODETEXT) )
		return CF_UNICODETEXT;
	else if( IsClipboardFormatAvailable(CF_DIB) )
		return CF_DIB;
	else if( IsClipboardFormatAvailable(CF_HDROP) )
		return CF_HDROP;

	Close();

	return 0;
}