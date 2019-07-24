#include "SceneChangeButton.h"


SceneChangeButton::SceneChangeButton()
{
	PosRC = { 0, 0, 0, 0 };
	ImageRC = {0, 0, 0, 0};
	Click = false;
	MouseOn = false;
	FrameCount = 0;
	FrameCountMax = 0;
}

SceneChangeButton::~SceneChangeButton()
{
}

void SceneChangeButton::SetMousePos(POINT pt)
{
	mouse = pt;
}

void SceneChangeButton::SetClick(bool bClick)
{
	Click = bClick;
}

bool SceneChangeButton::GetClick() const
{
	return Click;
}

void SceneChangeButton::Init(TCHAR * pFileName, int iFrameCountMax, RECT Posrc, RECT Imagerc)
{
	Image.Load(pFileName);

	FrameCountMax = iFrameCountMax;

	PosRC = Posrc;
	// PosX, PosY, SizeX, SizeY

	ImageRC = Imagerc;
	// left : 이미지시작점x, top : 이미지시작점y, right  : 이미지가로사이즈, bottom : 이미지세로사이즈
	//												= SizeX                = SizeY

	OnMouse.Set("resource/bgm/SFX_Button_On.ogg", 2);
	ClickMouse.Set("resource/bgm/SFX_Button_Off.ogg", 2);
}

void SceneChangeButton::Render(HDC hdc)
{
	Image.TransparentBlt(hdc, PosRC.left, PosRC.top, PosRC.right, PosRC.bottom, ImageRC.left, ImageRC.top, ImageRC.right, ImageRC.bottom, RGB(0, 255, 0));

#ifdef _DEBUG
	TCHAR str[128] = {};

	wsprintf(str, L"Button Pos : %d %d", PosRC.left, PosRC.top);
	TextOut(hdc, 600, 30, str, lstrlen(str));

#endif // _DEBUG

}

void SceneChangeButton::Update()
{
	if (CheckMouseOnButton())
	{
		if (!MouseOn)
			OnMouse.Play();
		FrameCount = 1;
		MouseOn = true;
	}

	else
	{
		FrameCount = 0;
		MouseOn = false;
	}

	ImageRC.left = ImageRC.right * FrameCount;
}

void SceneChangeButton::Input()
{
	if (KEYDOWN(VK_LBUTTON) )
	{
		if (MouseOn)
		{
			Click = true;
			ClickMouse.Play();
		}
	}
	
	if(KEYUP(VK_LBUTTON))
	{
		Click = false;
	}
}

// 마우스가 버튼 위에있는지 체크! 위에있으면 true 아니면 false
bool SceneChangeButton::CheckMouseOnButton()
{
	RECT ButtonCollider = { PosRC.left, PosRC.top, PosRC.left + PosRC.right, PosRC.top + PosRC.bottom };

	if (PtInRect(&ButtonCollider, mouse))
	{
		return true;
	}

	return false;
}
