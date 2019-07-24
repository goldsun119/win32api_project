#pragma once
#include "Header.h"

struct BUBBLEPOS
{
	POINT pt1;
	POINT pt2;
	POINT pt3;
	POINT pt4;
};

class Bubble
{
public:
	Bubble();
	~Bubble();

private:
	int posX;
	int posY;
	int imgX;
	int imgY;
	int length;
	int count;
	bool bomb;
	CImage img;
	CImage img2;

	int ImageCount1;
	int ImageCount1Check;
	int ImageCount2;

	TILEINFO Tile[TILEY][TILEX];
	int idxX;
	int idxY;

	bool Die;
	bool Coll;
	vector<BUBBLEPOS> CheckPos;
	vector<POINT>	CheckIndex;
	vector<POINT>	BreakIndex;
	bool Check[4];

	bool RenderUpdate;

public:
	Bubble(int x, int y, int l, TILEINFO tile[TILEY][TILEX]);
	void SetimgX(int a);
	void SetimgY(int a);
	void SetBomb();
	void SetCount(int a);
	void SetTileInfo(TILEINFO tile[TILEY][TILEX]);
	void SetDie(bool b);
	void SetColl(bool b);
	void SetPosX(int x);
	void SetPosY(int y);
	void SetInfo(int x, int y, int l, TILEINFO tile[TILEY][TILEX]);
	void SetRenderUpdate(bool b);


public:
	int GetCount() const;
	bool GetBomb() const;
	int GetimgX() const;
	int GetimgY() const;
	bool GetDie() const;
	TILEINFO GetTileInfo(int x, int y)	const;
	int GetCount2() const;
	bool GetColl() const;
	bool GetRenderUpdate() const;

	vector<POINT>	GetBreakIndex()	const;
	vector<POINT>	GetCheckIndex()	const;

public:
	void Draw(HDC hdc);

	void Init(int x, int y, int l, TILEINFO tile[TILEY][TILEX]);
	void Render(HDC hdc);
	void Update();
};

