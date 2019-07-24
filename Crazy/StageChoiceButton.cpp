#include "StageChoiceButton.h"



StageChoiceButton::StageChoiceButton()
{
	eStage = STAGE1;
	PosRC = { 0,0,0,0 };
	ImageRC = { 0,0,0,0 };
	Click = false;
}

StageChoiceButton::~StageChoiceButton()
{
}

void StageChoiceButton::SetStage(GAMESTAGE eS)
{
	eStage = eS;
}

void StageChoiceButton::SetClick(bool bClick)
{
	Click = bClick;
}

void StageChoiceButton::SetMousePos(POINT pt)
{
	mouse = pt;
}

GAMESTAGE StageChoiceButton::GetStage() const
{
	return eStage;
}

bool StageChoiceButton::GetClick() const
{
	return Click;
}

void StageChoiceButton::Init(TCHAR * pFileName, GAMESTAGE eS, RECT Posrc, RECT Imagerc)
{
	Image.Load(pFileName);
	eStage = eS;
	PosRC = Posrc;
	ImageRC = Imagerc;
	MapPosRC = { 475, 340, 625, 470 };

	TCHAR str[128] = {};
	wsprintf(str, L"resource/map/Stage%d.png", eS);
	MapImage.Load(str);

}

void StageChoiceButton::Render(HDC hdc)
{
	if (!Image.IsNull() && !MapImage.IsNull())
	{
		Image.TransparentBlt(hdc, PosRC.left, PosRC.top, PosRC.right, PosRC.bottom, ImageRC.left, ImageRC.top, ImageRC.right, ImageRC.bottom, RGB(0, 255, 0));
		MapImage.Draw(hdc, MapPosRC, { 0, 0, MapImage.GetWidth(), MapImage.GetHeight() });
	}
}

void StageChoiceButton::Update()
{
}

void StageChoiceButton::Input()
{
	if (KEYDOWN(VK_LBUTTON) && CheckMouseOnButton())
	{
		if (!Click)
			Click = true;

		else
			Click = false;
	}
}

bool StageChoiceButton::CheckMouseOnButton()
{
	RECT ButtonCollider = { PosRC.left, PosRC.top, PosRC.left + PosRC.right, PosRC.top + PosRC.bottom };

	if (PtInRect(&ButtonCollider, mouse))
	{
		return true;
	}

	return false;
}
