#pragma once
#include "Header.h"
#include "Sound.h"

// ��� ��ȯ�ϴ� ��ư�ε� ex) GameStart, ������, �غ� ��ư ��� 

class SceneChangeButton
{
public:
	SceneChangeButton();
	~SceneChangeButton();

private:
	RECT PosRC;
	RECT ImageRC;
	bool Click;				// ��ư�� Ŭ���߳�?
	bool MouseOn;			// ��ư���� ���콺�� �÷�����?
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

