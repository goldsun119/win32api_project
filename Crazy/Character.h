#pragma once
#include "Header.h"
#include "Bubble.h"
#include "Item.h"
#include "Sound.h"

class Character
{
public:
	Character();
	~Character();

private:
	int iPosX;
	int iPosY;
	int iSizeX;
	int iSizeY;

	int iImagePosX;
	int iImagePosY;
	int iImageSizeX;
	int iImageSizeY;

	int iSpeed;

	bool Move;

	int FrameCount;
	int FrameCountMax[DIR_END];
	DIR eDir;

	RECT ColliderRC;
	RECT IntersectRC;

	CImage Image;
	int KeyDown;

	int iCheckPos[2];

	TILEINFO Tile[TILEY][TILEX];
	bool TileInfoEmpty;

	CHARACTER eChacter;
	STATE	eState;

	vector<POINT>	BubbleBreakIndex;
	vector<POINT>	BubbleIndex;
	Bubble		Bomb[10];

	// 아이템
	int iSpeedCount;
	int iSpeedCountMax;
	int iBubbleCount;
	int iBubbleCountMax;
	int iStreamCount;
	int iStreamCountMax;

	vector<Bubble*> bomb;

	int AttackTime;
	int AttackTimeLimit;
	bool Attack;
	int BubbleCheckCount;
	int NotWalkFrame;
	int FrameTime;

	bool DieCheck;
	bool Caged;

	SoundPlay BubbleSet;
	SoundPlay BubbleBomb;
	SoundPlay InBubble;
	SoundPlay Die;
	SoundPlay Item;

public:
	void SetPosX(int x);
	void SetPosY(int y);
	void SetSizeX(int x);
	void SetSizeY(int y);
	void SetImagePosX(int x);
	void SetImagePosY(int y);
	void SetImageSizeX(int x);
	void SetImageSizeY(int y);
	void SetDir(int iDir);
	void SetFrameCountMax(int x, int idx);
	void SetSpeed(int Speed);
	void SetTileInfo(TILEINFO tile[TILEY][TILEX]);
	void SetTileInfo(int x, int y, TILEINFO tile);
	void SetCharacter(CHARACTER eC);
	void SetStreamCount(int iCount);
	void BubbleIdxClear();

public:
	int GetPosX() const;
	int GetPosY() const;
	int GetSpeed() const;
	RECT GetColliderRC() const;
	bool GetTileInfoEmpty() const;
	CHARACTER GetChacter() const;
	vector<POINT> GetBubbleBreakIndex() const;
	TILEINFO GetTileInfo(int x, int y)	const;

	void LoadTexture(TCHAR* pPath);
	void ChangeTexture(TCHAR* pFileName);

	bool CanMove();
	bool CanMove(int x, int y);
	bool StreamIn(int x, int y);
	int EatItem(int x, int y);

public:
	void Init(TCHAR* pFileName, int* iFrameCountMax, int x, int y, CHARACTER eC);		// 파일경로, 애니메이션할때 framecountMax값, 플레이어 처음 위치(인덱스로 생각), 캐릭터 종류(Bazzi, Dao)
	void Render(HDC hdc);
	void Update();
	void Input();
};

