#pragma once
#include "Header.h"

class CItem
{
public:
	CItem();
	CItem(const CItem& item);
	~CItem();

private:
	int ItemNum;
	CImage Image;
	RECT PosRC;

public:
	void SetItemNum(int iNum);
	void SetPos(RECT rc);

public:
	int GetItemNum() const;

public:
	void Init(const int& iNum, const RECT& rc);
	void Render(HDC hdc);
	void Update();
	void Input();
};

