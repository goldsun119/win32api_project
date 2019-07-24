#pragma once
#include "Header.h"
#include "Sound.h"

class Background
{
public:
	Background();
	~Background();

private:
	RECT RC;
	CImage Image;

	SoundPlay BGM;
	bool IsBGMPlaying;

public:
	RECT GetRC() const;

public:
	void Init(TCHAR* pFileName, RECT rc, const char* file, int type);		// 파일 경로, 이미지 크기
	void Render(HDC hdc);
	void Update();
	void Input();
	void BGMOnOff(bool on);
};

