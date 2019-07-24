#pragma once
#include "Header.h"

class StageChoiceButton
{
public:
	StageChoiceButton();
	~StageChoiceButton();

private:
	GAMESTAGE		eStage;
	CImage			Image;
	CImage			MapImage;
	RECT			PosRC;
	RECT			ImageRC;
	bool			Click;
	POINT			mouse;
	RECT			MapPosRC;

public:
	void SetStage(GAMESTAGE eS);
	void SetClick(bool bClick);
	void SetMousePos(POINT pt);

public:
	GAMESTAGE GetStage()	const;
	bool GetClick()	const;

public:
	void Init(TCHAR* pFileName, GAMESTAGE eS, RECT Posrc, RECT Imagerc);
	void Render(HDC hdc);
	void Update();
	void Input();

private:
	bool CheckMouseOnButton();
};

