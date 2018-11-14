#include "stdafx.h"
#include "Temp.h"


CTemp::CTemp(void)
{
}


CTemp::~CTemp(void)
{
}

void CTemp::Create(void)
{
#ifdef _MSC_VER
	tmpnam_s(FileName);
#else
	tmpnam(FileName);
#endif
}

void CTemp::Destroy(void)
{
	remove(FileName);
}

char* CTemp::GetFileName(void)
{
	return FileName;
}