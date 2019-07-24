#include "Character.h"
#include "Background.h"
#include "Bubble.h"
#include "Item.h"
#include "Sound.h"

Character::Character()
{
	iPosX = 100;
	iPosY = 100;
	iSizeX = 70;
	iSizeY = 70;
	iImagePosX = 0;
	iImagePosY = 0;
	iImageSizeX = 70;
	iImageSizeY = 70;
	iSpeed = 2;

	Move = false;
	FrameCount = 0;
	memset(FrameCountMax, 0, sizeof(FrameCountMax));
	eDir = DOWN;
	eState = WALK;

	ColliderRC = { 0, 0, 0, 0 };
	IntersectRC = { 0, 0, 0, 0 };
	KeyDown = -1;

	iCheckPos[0] = 0;
	iCheckPos[1] = 0;

	TileInfoEmpty = true;

	eChacter = BAZZI;

	iSpeedCount = 1;
	iSpeedCountMax = 3;
	iBubbleCount = 1;
	iBubbleCountMax = 3;
	iStreamCount = 1;
	iStreamCountMax = 5;
	AttackTime = 0;
	AttackTimeLimit = 7;
	Attack = false;
	BubbleCheckCount = 0;
	DieCheck = false;
	Caged = false;

	BubbleSet.Set("resource/bgm/SFX_Bubble_On.ogg", 2);
	BubbleBomb.Set("resource/bgm/SFX_Bubble_Off.ogg", 2);
	InBubble.Set("resource/bgm/SFX_Character_Fixed.ogg", 2);
	Die.Set("resource/bgm/SFX_Character_Die.ogg", 2);
	Item.Set("resource/bgm/SFX_Item_On.ogg", 2);

	for (int i = 0; i < 10; ++i)
	{
		Bomb[i].Init(0, 0, iStreamCount, Tile);
	}
}

Character::~Character()
{
}

void Character::SetPosX(int x)
{
	iPosX = x;
}

void Character::SetPosY(int y)
{
	iPosY = y;
}

void Character::SetSizeX(int x)
{
	iSizeX = x;
}

void Character::SetSizeY(int y)
{
	iSizeY = y;
}

void Character::SetImagePosX(int x)
{
	iImagePosX = x;
}

void Character::SetImagePosY(int y)
{
	iImagePosY = y;
}

void Character::SetImageSizeX(int x)
{
	iImageSizeX = x;
}

void Character::SetImageSizeY(int y)
{
	iImageSizeY = y;
}

void Character::SetDir(int iDir)
{
	eDir = (DIR)iDir;
}

void Character::SetFrameCountMax(int x, int idx)
{
	FrameCountMax[idx] = x;
}

void Character::SetSpeed(int Speed)
{
	iSpeed = Speed;
}

void Character::SetTileInfo(TILEINFO tile[TILEY][TILEX])
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = tile[i][j];
		}
	}

	TileInfoEmpty = false;
}

void Character::SetTileInfo(int x, int y, TILEINFO tile)
{
	Tile[y][x] = tile;
}

void Character::SetCharacter(CHARACTER eC)
{
	eChacter = eC;
}

void Character::SetStreamCount(int iCount) 
{
	iStreamCount = iCount;
}

void Character::BubbleIdxClear()
{
	BubbleIndex.clear();
}

int Character::GetPosX() const
{
	return iPosX;
}

int Character::GetPosY() const
{
	return iPosY;
}

int Character::GetSpeed() const
{
	return iSpeed;
}

RECT Character::GetColliderRC() const
{
	return ColliderRC;
}

bool Character::GetTileInfoEmpty() const
{
	return TileInfoEmpty;
}

CHARACTER Character::GetChacter() const
{
	return eChacter;
}

vector<POINT> Character::GetBubbleBreakIndex() const
{
	return BubbleBreakIndex;
}

TILEINFO Character::GetTileInfo(int x, int y) const
{
	return Tile[y][x];
}

void Character::LoadTexture(TCHAR * pPath)
{
	if (!Image.IsNull())
		Image.Destroy();
	Image.Load(pPath);
}

void Character::ChangeTexture(TCHAR * pFileName)
{
	if (!Image.IsNull())
		Image.Destroy();
	Image.Load(pFileName);
}

bool Character::CanMove()
{
	if (!TileInfoEmpty)
	{
		int x, y;
		x = iCheckPos[0] / 40;
		y = iCheckPos[1] / 40;

		if (Tile[y][x].Move)
		{
			return true;
		}
	}

	return false;
}

bool Character::CanMove(int x, int y)
{
	int X, Y;
	X = (x + 20) / 40;
	Y = y / 40;

	if (Tile[Y][X].Move)
	{
		return true;
	}

	return false;
}

bool Character::StreamIn(int x, int y)
{
	int X, Y;
	X = (x + 20) / 40;
	Y = y / 40;

	for (int i = 0; i < BubbleIndex.size(); ++i)
	{
		if (BubbleIndex[i].x == X && BubbleIndex[i].y == Y)
		{
			BubbleIdxClear();
			return true;
		}
	}
	BubbleIdxClear();
	return false;
}

int Character::EatItem(int x, int y)
{
	int X, Y;
	X = (x + 20) / 40;
	Y = y / 40;

	if (Tile[Y][X].Item == 0)
	{
		SetTile(X, Y, -1);
		//Tile[Y][X].Item = -1;
		if (iBubbleCount <= iBubbleCountMax)
			iBubbleCount += 1;

		return 0;
	}

	else if (Tile[Y][X].Item == 1)
	{
		SetTile(X, Y, -1);
		if (iStreamCount <= iStreamCountMax)
			iStreamCount += 1;
		return 1;
	}

	else if (Tile[Y][X].Item == 2)
	{
		SetTile(X, Y, -1);
		if (iSpeedCount <= iSpeedCountMax)
			iSpeedCount += 1;
		return 2;
	}

	else if (Tile[Y][X].Item == 3)
	{
		SetTile(X, Y, -1);
		iStreamCount = iStreamCountMax;
		return 3;
	}

	else if (Tile[Y][X].Item == 4)
	{
		SetTile(X, Y, -1);
		iSpeedCount = iSpeedCountMax;
		return 4;
	}

	return -1;
}

void Character::Init(TCHAR * pFileName, int* iFrameCountMax, int x, int y, CHARACTER eC)
{
	if(Image.IsNull())
		Image.Load(pFileName);

	for (int i = 0; i < DIR_END; ++i)
	{
		FrameCountMax[i] = iFrameCountMax[i];
	}

	iPosX = x * 40 - 40;
	iPosY = y * 40 - 30;

	eChacter = eC;
	if (eChacter == BAZZI)
	{
		iSpeedCount = 5;
		iSpeedCountMax = 9;
		iBubbleCount = 1;
		iBubbleCountMax = 6;
		iStreamCount = 1;
		iStreamCountMax = 7;
	}

	else if (eChacter == DAO)
	{
		iSpeedCount = 5;
		iSpeedCountMax = 7;
		iBubbleCount = 1;
		iBubbleCountMax = 10;
		iStreamCount = 1;
		iStreamCountMax = 7;
	}

	iSpeed = 2;
	Move = false;
	FrameCount = 0;
	eDir = DOWN;
	eState = WALK;
	NotWalkFrame = 0;
	FrameTime = 0;
	DieCheck = false;
	Caged = false;
}

void Character::Render(HDC hdc)
{
	Image.TransparentBlt(hdc, iPosX, iPosY, iSizeX, iSizeY , iImagePosX, iImagePosY, iImageSizeX, iImageSizeY, RGB(0, 255, 0));

	vector<Bubble*>::iterator	iter;
	vector<Bubble*>::iterator	iterEnd = bomb.end();

	for (iter = bomb.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hdc);
	}


	/*for (int i = 1; i <= BubbleCheckCount; ++i)
	{
		if(Bomb[i].GetRenderUpdate())
			Bomb[i].Render(hdc);
	}*/

#ifdef _DEBUG
	static TCHAR str[128] = {};

	if (eChacter == BAZZI)
	{
		wsprintf(str, L"Bazzi Pos : %d %d", iPosX, iPosY);
		TextOut(hdc, 600, 30, str, lstrlen(str));

		wsprintf(str, L"Bazzi ImagePos : %d %d", iImagePosX, iImagePosY);
		TextOut(hdc, 600, 60, str, lstrlen(str));
	}
	else if (eChacter == DAO)
	{
		wsprintf(str, L"Dao Pos : %d %d", iPosX, iPosY);
		TextOut(hdc, 600, 90, str, lstrlen(str));

		wsprintf(str, L"Dao ImagePos : %d %d", iImagePosX, iImagePosY);
		TextOut(hdc, 600, 120, str, lstrlen(str));
	}
	FrameRect(hdc, &ColliderRC, CreateSolidBrush(RGB(0, 0, 255)));
#endif // _DEBUG
}

void Character::Update()
{
	if(Attack)
		AttackTime++;

	if (AttackTimeLimit < AttackTime)				// 이건 한꺼번에 물풍선 많이 출력되는거 방지
	{
		AttackTime = 0;
		if(BubbleCheckCount < iBubbleCount)
			Attack = false;
	}

	//std::vector<Bubble*>::iterator v = bomb.begin();
	for (auto& v : bomb)
	{
		v->Update();
		if (v->GetBomb() && !v->GetColl() && v->GetDie())
		{
			BubbleCheckCount--;
			v->SetColl(true);
			BubbleBomb.Play();
		}

		for (int i = 0; i < v->GetBreakIndex().size(); ++i)
		{
			POINT idx = v->GetBreakIndex()[i];
			BubbleBreakIndex.push_back(idx);
		}

		
		if (v->GetColl())
		{
			for (int i = 0; i < v->GetCheckIndex().size(); ++i)
			{
				POINT idx = v->GetCheckIndex()[i];
				BubbleIndex.push_back(idx);
			}
			v->SetColl(false);
				if(bomb.size()>0)
					bomb.erase(bomb.begin());
		}
	}

	/*for (int i = 1; i <= BubbleCheckCount; ++i)
	{
		if (Bomb[i].GetRenderUpdate())
		{
			Bomb[i].Update();

			if (Bomb[i].GetBomb() && !Bomb[i].GetColl() && Bomb[i].GetDie())
			{
				BubbleCheckCount--;
				Bomb[i].SetColl(true);
				BubbleBomb.Play();
			}

			for (int j = 0; j < Bomb[i].GetBreakIndex().size(); ++j)
			{
				POINT idx = Bomb[i].GetBreakIndex()[j];
				BubbleBreakIndex.push_back(idx);
			}


			if (Bomb[i].GetColl())
			{
				for (int j = 0; j < Bomb[i].GetCheckIndex().size(); ++j)
				{
 					POINT idx = Bomb[i].GetCheckIndex()[j];
					BubbleIndex.push_back(idx);
				}
			}
		}
	}*/

	iCheckPos[0] = iPosX;
	iCheckPos[1] = iPosY;

	ColliderRC = { iCheckPos[0] + 20, iCheckPos[1] + 20, iCheckPos[0] + iSizeX - 10, iCheckPos[1] + iSizeY};
	
	int CenterX = ColliderRC.left + (ColliderRC.right - ColliderRC.left) / 2;
	int CenterY = ColliderRC.top + (ColliderRC.bottom - ColliderRC.top) / 2;


	if (StreamIn(CenterX, CenterY) && !Caged)
	{
		eState = CAGED;
		Caged = true;
	}

	if (Move && !DieCheck)
	{
		if (EatItem(CenterX, CenterY) != -1)
		{
			Item.Play();
		}

		if (iImagePosX < iImageSizeX * FrameCountMax[eDir] || iImagePosX < Image.GetWidth())
		{
			FrameCount++;

			FrameCount %= FrameCountMax[eDir];
		}

		switch (eDir)
		{
		case UP:
			iCheckPos[1] -= iSpeed;
			if (CanMove(CenterX, ColliderRC.top))
			{
				if (eState == WALK)
				{
					iPosY -= iSpeed * iSpeedCount;
				}
				else
				{
					iPosY -= 5;
				}
			}
			break;
		case DOWN:
			iCheckPos[1] += iSpeed;
			if (CanMove(CenterX, ColliderRC.bottom))
			{
				if (eState == WALK)
				{
					iPosY += iSpeed * iSpeedCount;
				}

				else
				{
					iPosY += 5;
				}
			}

			break;
		case RIGHT:
			iCheckPos[0] += iSpeed;
			if (CanMove(ColliderRC.right, CenterY))
			{
				if (eState == WALK)
				{
					iPosX += iSpeed * iSpeedCount;
				}

				else
				{
					iPosX += 5;
				}
			}
			break;
		case LEFT:
			iCheckPos[0] -= iSpeed;
			if (CanMove(ColliderRC.left - 10, CenterY))
			{
				if (eState == WALK)
				{
					iPosX -= iSpeed * iSpeedCount;
				}

				else
				{
					iPosX -= 5;
				}
			}
			break;
		case DIR_END:
			break;
		default:
			break;
		}
	}
	if (eState == WALK)
	{
		iImagePosX = iImageSizeX * FrameCount;
		iImagePosY = iImageSizeY * eDir;
	}

	int MaxCount[] = { 5, 5, 4, 4, 4, 5, 6 };
	if (eState != WALK)
	{
		if (iImagePosX < iImageSizeX * FrameCountMax[eDir] || iImagePosX < Image.GetWidth())
		{
			FrameTime++;
			if (FrameTime > 3)
			{
				NotWalkFrame++;
				FrameTime = 0;
			}
			if(NotWalkFrame == MaxCount[eState])
				NotWalkFrame = MaxCount[eState];
		}
	}
	switch (eState)
	{
	case CAGED:
		iImagePosX = iImageSizeX * NotWalkFrame;
		iImagePosY = iImageSizeY * eState;
		if (NotWalkFrame == MaxCount[eState])
		{
			eState = DIE;
			NotWalkFrame = 0;
			FrameTime = 0;
		}
		break;
	case ALIVE:
		iImagePosX = iImageSizeX * NotWalkFrame;
		iImagePosY = iImageSizeY * eState; 
		if (NotWalkFrame == MaxCount[eState])
		{
			eState = WALK;
			eDir = DOWN;
		}

		break;
	case DIE:
		iImagePosX = iImageSizeX * NotWalkFrame;
		iImagePosY = iImageSizeY * eState;
		DieCheck = true;
		break;
	default:
		break;
	}
}

void Character::Input()
{
	if (!DieCheck)
	{
		if (eChacter == DAO)
		{
			if (KEYDOWN(VK_LEFT))
			{
				eDir = LEFT;
				Move = true;
			}

			else if (KEYDOWN(VK_RIGHT))
			{
				eDir = RIGHT;
				Move = true;
			}

			else if (KEYDOWN(VK_UP))
			{
				eDir = UP;
				Move = true;
			}

			else if (KEYDOWN(VK_DOWN))
			{
				eDir = DOWN;
				Move = true;
			}

			else
			{
				Move = false;
				FrameCount = 0;
			}

			if (KEYDOWN(VK_RSHIFT) && !Attack)
			{
				//공격
				if (BubbleCheckCount < iBubbleCount)
				{
					BubbleCheckCount++;
					BubbleSet.Play();
					Bubble* b = new Bubble(iPosX, iPosY, iStreamCount, Tile);
					bomb.push_back(b);

					/*Bomb[BubbleCheckCount].SetInfo(iPosX, iPosY, iStreamCount, Tile);
					Bomb[BubbleCheckCount].SetRenderUpdate(true);*/
					Attack = true;
				}
			}
		}

		else if (eChacter == BAZZI)
		{
			if (KEYDOWN('A'))
			{
				eDir = LEFT;
				Move = true;
			}

			else if (KEYDOWN('D'))
			{
				eDir = RIGHT;
				Move = true;
			}

			else if (KEYDOWN('W'))
			{
				eDir = UP;
				Move = true;
			}

			else if (KEYDOWN('S'))
			{
				eDir = DOWN;
				Move = true;
			}

			else
			{
				Move = false;
				FrameCount = 0;
			}

			if (KEYDOWN(VK_LSHIFT) && !Attack)
			{
				//공격
				if (BubbleCheckCount < iBubbleCount)
				{
					BubbleCheckCount++;
					BubbleSet.Play();
					Bubble* b = new Bubble(iPosX, iPosY, iStreamCount, Tile);
					bomb.push_back(b);

					/*Bomb[BubbleCheckCount].SetInfo(iPosX, iPosY, iStreamCount, Tile);
					Bomb[BubbleCheckCount].SetRenderUpdate(true);*/
					Attack = true;
				}
			}
		}
	}
}