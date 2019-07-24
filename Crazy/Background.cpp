#include "Background.h"


Background::Background()
{
	RC = { 0, 0, WINSIZE_W, WINSIZE_H };
}

Background::~Background()
{
	BGM.Stop();
}

RECT Background::GetRC() const
{
	return RC;
}

void Background::Init(TCHAR * pFileName, RECT rc, const char* file, int type)
{
	Image.Load(pFileName);
	RC = rc;
	BGM.Set(file, type);
}

void Background::Render(HDC hdc)
{
	Image.TransparentBlt(hdc, RC, RGB(0, 255, 0));
}

void Background::Update()
{
}

void Background::Input()
{
}

void Background::BGMOnOff(bool on)
{
	IsBGMPlaying = on;
	if (IsBGMPlaying)
		BGM.Play();
	else BGM.Stop();
}
