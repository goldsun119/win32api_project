#include "Item.h"

CItem::CItem()
{
	PosRC = { 0, 0, 0, 0 };
	ItemNum = -1;
}

CItem::CItem(const CItem & item)
{
	ItemNum = item.ItemNum;
	PosRC = item.PosRC;
	Image = item.Image;
}

CItem::~CItem()
{
}

void CItem::SetItemNum(int iNum)
{
	ItemNum = iNum;
	TCHAR str[128] = {};
	wsprintf(str, L"resource/item/Item%d.bmp", iNum);

	if (!Image.IsNull())
		Image.Destroy();
	Image.Load(str);
}

void CItem::SetPos(RECT rc)
{
	PosRC = rc;
}

int CItem::GetItemNum() const
{
	return ItemNum;
}

void CItem::Init(const int& iNum, const RECT& rc)
{
	TCHAR str[128] = {};
	wsprintf(str, L"resource/item/Item%d.bmp", iNum);

	Image.Load(str);
	PosRC = rc;
}

void CItem::Render(HDC hdc)
{
	Image.TransparentBlt(hdc, PosRC, { 0, 0, 40, 40 }, RGB(0, 255, 0));
}

void CItem::Update()
{
}

void CItem::Input()
{
}
