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
	tmpnam_s(FileName);
}

void CTemp::Destroy(void)
{
	remove(FileName);
}

char* CTemp::GetFileName(void)
{
	return FileName;
}