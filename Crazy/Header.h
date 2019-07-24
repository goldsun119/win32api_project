#pragma once
#include <windows.h>
#include <TCHAR.h>
#include <atlImage.h>
#include <string>
#include "resource.h"
#include <random>
#include <time.h>
#include <vector>
#include <vector>
#include "fmod.hpp"
#pragma comment (lib, "fmodex_vc.lib")

using namespace std;
using namespace FMOD;


enum SCENE
{
	MAPTOOL,
	INGAME
};

enum GAMESTAGE
{
	LOGO = -2,
	LOBBY = -1,
	STAGE1 = 0,
	STAGE2 = 1,
	STAGE3 = 2
};

enum DIR
{
	UP, DOWN, RIGHT, LEFT, DIR_END
};

enum STATE
{
	WALK,
	CAGED = 4,
	ALIVE,
	DIE,
	DIEEND
};

enum CHARACTER
{
	BAZZI, DAO
};

struct TILEINFO {
	RECT rc;				//->타일 그려줄때 필요한거
	bool Break;
	bool Move;				// 가고 못가고 
	bool Push;
	int IndexX;
	int IndexY;
	int ImageNum;
	int Item;				// 아이템 -1일땐 아이템 출력 X
};

// 동시 입력 가능 
#define KEYPUSH(a)	GetAsyncKeyState(a) & 0x8001
#define KEYDOWN(a)	GetAsyncKeyState(a) & 0x8000
#define KEYUP(a)	GetAsyncKeyState(a) & 0x0001

#define WINSIZE_W 800
#define WINSIZE_H 600

#define BLANK_X 20
#define BLANK_Y 40

#define TILEX 17
#define TILEY 15
#define BOXNUM 5

#define ITEMRATE 10

static TILEINFO Tile[TILEY][TILEX];
void SetTile(int x, int y, int item);
static vector<POINT>	BubbleIndex;
void SetBubbleIndex(int x, int y);