#pragma once
#include "Header.h"
#include "Sound.h"

// 장면 전환하는 버튼인데 ex) GameStart, 나가기, 준비 버튼 등등 

class SceneChangeButton
{
public:
	SceneChangeButton();
	~SceneChangeButton();

private:
	RECT PosRC;
	RECT ImageRC;
	bool Click;				// 버튼을 클릭했냐?
	bool MouseOn;			// 버튼위에 마우스를 올려놨냐?
	int	 FrameCountMax;
	int  FrameCount;
	CImage Image;
	POINT mouse;
	SoundPlay	ClickMouse;
	SoundPlay OnMouse;


public:
	void SetMousePos(POINT pt);
	void SetClick(bool bClick);

public:
	bool GetClick()	const;

public:
	void Init(TCHAR* pFileName, int iFrameCountMax, RECT Posrc, RECT Imagerc);
	void Render(HDC hdc);
	void Update();
	void Input();

private:
	bool CheckMouseOnButton();
};

