#include "Bubble.h"

Bubble::Bubble()
{
	RenderUpdate = false;
}

Bubble::~Bubble()
{
}

Bubble::Bubble(int x, int y, int l, TILEINFO tile[TILEY][TILEX])
{
	img.Load(L"resource/bubble/1.png");
	img2.Load(L"resource/bubble/2.bmp");

	idxX = x / 40;
	idxY = y / 40;
	posX = idxX * 40 + 10;
	posY = idxY * 40 + 20;
	
	length = l;
	imgX = 0;
	imgY = 0;
	count = 0;
	bomb = false;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = tile[i][j];
		}
	}

	Die = false;
	ImageCount1 = 0;
	ImageCount1Check = 0;
	ImageCount2 = 0;

	for (int i = 0; i < 4; ++i)
	{
		Check[i] = false;
	}

	Coll = false;
}

void Bubble::SetimgX(int a)
{
	imgX = a;
}

void Bubble::SetimgY(int a)
{
	imgY = a;
}

int Bubble::GetimgX() const
{
	return imgX;
}

int Bubble::GetimgY() const
{
	return imgY;
}

bool Bubble::GetDie() const
{
	return Die;
}

TILEINFO Bubble::GetTileInfo(int x, int y) const
{
	return Tile[y][x];
}

int Bubble::GetCount2() const
{
	return ImageCount2;
}

bool Bubble::GetColl() const
{
	return Coll;
}

bool Bubble::GetRenderUpdate() const
{
	return RenderUpdate;
} 

vector<POINT> Bubble::GetBreakIndex() const
{
	return BreakIndex;
}

vector<POINT> Bubble::GetCheckIndex() const
{
	return CheckIndex;
}

void Bubble::SetCount(int a)
{
	count = a;
}

void Bubble::SetTileInfo(TILEINFO tile[TILEY][TILEX])
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = tile[i][j];
		}
	}
}

void Bubble::SetDie(bool b)
{
	Die = b;
}

void Bubble::SetColl(bool b)
{
	Coll = b;
}

void Bubble::SetPosX(int x)
{
	idxX = x / 40;
	posX = idxX * 40 + 10;
}

void Bubble::SetPosY(int y)
{
	idxY = y / 40;
	posY = idxY * 40 + 20;
}

void Bubble::SetInfo(int x, int y, int l, TILEINFO tile[TILEY][TILEX])
{
	idxX = x / 40;
	idxY = y / 40;
	posX = idxX * 40 + 10;
	posY = idxY * 40 + 20;

	imgX = 0;
	imgY = 0;
	count = 0;
	bomb = false;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = tile[i][j];
		}
	}

	Die = false;
	ImageCount1 = 0;
	ImageCount1Check = 0;
	ImageCount2 = 0;

	for (int i = 0; i < 4; ++i)
	{
		Check[i] = false;
	}

	Coll = false;
	RenderUpdate = false;
	CheckIndex.clear();
}

void Bubble::SetRenderUpdate(bool b)
{
	RenderUpdate = b;
}

int Bubble::GetCount() const
{
	return count;
}

void Bubble::SetBomb()
{
	bomb = true;
}

bool Bubble::GetBomb() const
{
	return bomb;
}

void Bubble::Draw(HDC hdc)
{
	//if (!bomb)
	//	img.Draw(hdc, RECT{ posX, posY, posX + 60, posY + 70}, RECT{ imgX, imgY, imgX + 72, imgY + 87 });

	//else
	//{
	//	img2.TransparentBlt(hdc, posX + 10, posY + 20, 40, 40, 40 * count, 0, 40, 40, RGB(0, 255, 0));

	//	int X[4], Y[4];
	//	for (int i = 1; i <= length; ++i)
	//	{
	//		X[0] = (posX + 10 - 40 * i + 40) / 40;			Y[0] = (posY + 20) / 40;					// ¿Þ
	//		X[1] = (posX + 10 + 40) / 40;					Y[1] = (posY + 20 - 40 * i) / 40;			// À§
	//		X[2] = (posX + 10 + 40 * i + 40) / 40;			Y[2] = (posY + 20) / 40;					// ¿À
	//		X[3] = (posX + 10 + 40) / 40;					Y[3] = (posY + 20 + 40 * i) / 40;			// ¾Æ

	//		if (i != length)
	//		{
	//			img2.TransparentBlt(hdc, posX + 10 - 40 * i, posY + 20, 40, 40, 40 * count, 320, 40, 40, RGB(0, 255, 0));
	//		}
	//		else
	//		{
	//			img2.TransparentBlt(hdc, posX + 10 - 40 * i, posY + 20, 40, 40, 40 * count, 160, 40, 40, RGB(0, 255, 0));
	//		}

	//		if (i != length)
	//		{
	//			img2.TransparentBlt(hdc, posX + 10, posY + 20 - 40 * i, 40, 40, 40 * count, 200, 40, 40, RGB(0, 255, 0));
	//		}

	//		else
	//		{
	//			img2.TransparentBlt(hdc, posX + 10, posY + 20 - 40 * i, 40, 40, 40 * count, 40, 40, 40, RGB(0, 255, 0));

	//		}

	//		if (i != length)
	//		{
	//			img2.TransparentBlt(hdc, posX + 10 + 40 * i, posY + 20, 40, 40, 40 * count, 280, 40, 40, RGB(0, 255, 0));
	//		}
	//		else
	//		{
	//			img2.TransparentBlt(hdc, posX + 10 + 40 * i, posY + 20, 40, 40, 40 * count, 120, 40, 40, RGB(0, 255, 0));
	//		}

	//		if (i != length)
	//		{
	//			img2.TransparentBlt(hdc, posX + 10, posY + 20 + 40 * i, 40, 40, 40 * count, 80, 40, 40, RGB(0, 255, 0));
	//		}

	//		else
	//		{
	//			img2.TransparentBlt(hdc, posX + 10, posY + 20 + 40 * i, 40, 40, 40 * count, 240, 40, 40, RGB(0, 255, 0));
	//		}

	//	}
	//}
}

void Bubble::Init(int x, int y, int l, TILEINFO tile[TILEY][TILEX])
{
	idxX = x / 40;
	idxY = y / 40;
	posX = idxX * 40 + 10;
	posY = idxY * 40 + 20;

	length = l;
	imgX = 0;
	imgY = 0;
	count = 0;
	bomb = false;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = tile[i][j];
		}
	}

	Die = false;
	ImageCount1 = 0;
	ImageCount1Check = 0;
	ImageCount2 = 0;

	for (int i = 0; i < 4; ++i)
	{
		Check[i] = false;
	}

	Coll = false;
	RenderUpdate = false;
	CheckIndex.clear();
}

void Bubble::Render(HDC hdc)
{
	if (!bomb)
		img.Draw(hdc, posX, posY, 60, 70, 0 + (72 * ImageCount1), 0, 72, 87);

	else
	{
		if (!Die)
		{
			img2.TransparentBlt(hdc, posX + 10, posY + 20, 40, 40, 40 * ImageCount2, 0, 40, 40, RGB(0, 255, 0));

			for (int i = 1; i <= length; ++i)
			{
				if (CheckIndex.size() < length * 4)
				{
					POINT pt;
					pt.x = (posX + 10 - 40 * i + 40) / 40;			pt.y = (posY + 20) / 40;					// ¿Þ
					CheckIndex.push_back(pt);
					pt.x = (posX + 10 + 40) / 40;					pt.y = (posY + 20 - 40 * i) / 40;		// À§
					CheckIndex.push_back(pt);
					pt.x = (posX + 10 + 40 * i + 40) / 40;			pt.y = (posY + 20) / 40;					// ¿À
					CheckIndex.push_back(pt);
					pt.x = (posX + 10 + 40) / 40;					pt.y = (posY + 20 + 40 * i) / 40;		// ¾Æ
					CheckIndex.push_back(pt);
				}
				for (int k = 0; k < CheckIndex.size(); ++k)
				{
					if (CheckIndex[k].y >= 0 && CheckIndex[k].x >= 0)
					{
						if (!Tile[CheckIndex[k].y][CheckIndex[k].x].Move)
						{
							if (!Check[k % 4])
							{
								Check[k % 4] = true;
								POINT idx = { Tile[CheckIndex[k].y][CheckIndex[k].x].IndexX , Tile[CheckIndex[k].y][CheckIndex[k].x].IndexY };
								BreakIndex.push_back(idx);
							}
						}
					}
				}
				// ¿Þ
				if (!Check[0])
				{
					if (i != length)
					{
						img2.TransparentBlt(hdc, posX + 10 - 40 * i, posY + 20, 40, 40, 40 * ImageCount2, 320, 40, 40, RGB(0, 255, 0));
					}

					else
					{
						img2.TransparentBlt(hdc, posX + 10 - 40 * i, posY + 20, 40, 40, 40 * ImageCount2, 160, 40, 40, RGB(0, 255, 0));
					}
				}


				// À§
				if (!Check[1])
				{
					if (i != length)
					{
						img2.TransparentBlt(hdc, posX + 10, posY + 20 - 40 * i, 40, 40, 40 * ImageCount2, 200, 40, 40, RGB(0, 255, 0));
					}

					else
					{
						img2.TransparentBlt(hdc, posX + 10, posY + 20 - 40 * i, 40, 40, 40 * ImageCount2, 40, 40, 40, RGB(0, 255, 0));

					}
				}

				// ¿À
				if (!Check[2])
				{
					if (i != length)
					{
						img2.TransparentBlt(hdc, posX + 10 + 40 * i, posY + 20, 40, 40, 40 * ImageCount2, 280, 40, 40, RGB(0, 255, 0));
					}

					else
					{
						img2.TransparentBlt(hdc, posX + 10 + 40 * i, posY + 20, 40, 40, 40 * ImageCount2, 120, 40, 40, RGB(0, 255, 0));
					}

				}

				// ¾Æ
				if (!Check[3])
				{
					if (i != length)
					{
						img2.TransparentBlt(hdc, posX + 10, posY + 20 + 40 * i, 40, 40, 40 * ImageCount2, 80, 40, 40, RGB(0, 255, 0));
					}

					else
					{
						img2.TransparentBlt(hdc, posX + 10, posY + 20 + 40 * i, 40, 40, 40 * ImageCount2, 240, 40, 40, RGB(0, 255, 0));
					}
				}
			}
		}
	}
}

void Bubble::Update()
{
	if (!bomb)
	{
		ImageCount1++;
		if (ImageCount1 > 3)
		{
			ImageCount1 = 0;
			ImageCount1Check++;
			if (ImageCount1Check > 6)
			{
				bomb = true;
			}
		}
	}

	else
	{

		ImageCount2++;
		if (ImageCount2 >= 3)
		{
			Die = true;
			ImageCount2 = 0;
		}
	}
}
