#include "Header.h"
#include "Character.h"
#include "Background.h"
#include "SceneChangeButton.h"
#include "StageChoiceButton.h"
#include "Item.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;
HWND g_hWnd;


void TileClear();
void TileChangeInfo(int x, int y, int num);
void MousePos(HDC hdc);
void TileBreak(int x, int y);
void TileBreak(vector<POINT> idx);
void TileUpdate();

int SaveClick(POINT mouse);
int LoadClick(POINT mouse);
int BoxClick(POINT mouse);
int PauseClick(POINT mouse);
int* MousePosToIndex(POINT mouse);

void Init();
void Update();
void Input();
void Render(HDC hdc);
void Save(int num);
void Load(int num);

void TileRectangleRender(HDC hdc);
void SaveLoadButtonRender(HDC hdc);
void BoxButtonRender(HDC hdc);
void ItemRender(HDC hdc);

//TILEINFO Tile[TILEY][TILEX];
CImage BoxImage[BOXNUM];
int ChangeBox;
bool PickBox;
int TileSize[2];
int Idx[2];
int Pause = 1;

POINT mouse;
int SceneNum;
int StageNum;
bool LoadStage[3];
int iTime = 50;

RECT SaveRC[3] = { { 640, 100, 780, 130 },{ 640, 140, 780, 170 },{ 640, 180, 780, 210 } };				
RECT LoadRC[3] = { { 640, 250, 780, 280 },{ 640, 290, 780, 320 }, { 640, 330, 780, 360 } };
RECT BoxRC[BOXNUM] = { { 680, 400, 720, 440 }, { 730, 400, 770, 440 },
{ 680, 460, 720, 500 }, { 730, 460, 770, 500 }, { 680, 520, 720, 560} };
RECT PauseRC = {765, 5, 790, 25};

// 플레이어
Character Bazzi;
Character Dao;

// 배경
Background Logo;
Background Stage1_BK;
Background Lobby;

// 장면전환할때 쓰이는 버튼!
SceneChangeButton LogoButton;		// 로고의 게임시작버튼
SceneChangeButton LobbyButton;		// 로비의 게임시작버튼
SceneChangeButton ToLobbyButton;	// 나가기버튼

// 스테이지 선택버튼
StageChoiceButton StageButton[3];
int StageChoice = 0;

// 아이템
CImage Item[6];

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	hwnd;
	MSG 	msg;
	WNDCLASSEX	WndClass;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hwnd = CreateWindow(_T("Window Class Name"), _T("2018 Window Programming Midterm"), WS_OVERLAPPEDWINDOW,
		0, 0, WINSIZE_W + 9, WINSIZE_H + 32, NULL, NULL, hInstance, NULL);
	hInst = hInstance;
	g_hWnd = hwnd;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (iMsg) {
	case WM_CREATE:
		SetTimer(hwnd, 1, iTime, NULL);		// 키보드 입력때문에 
		TileClear();
		BoxImage[0].Load(L"resource/map/Box_-1.bmp");
		BoxImage[1].Load(L"resource/map/Box0.bmp");
		BoxImage[2].Load(L"resource/map/Box1.bmp");
		BoxImage[3].Load(L"resource/map/Box2.bmp");
		BoxImage[4].Load(L"resource/map/Nomove.bmp");
		Item[0].Load(L"resource/item/item-1.bmp");
		Item[1].Load(L"resource/item/item0.bmp");
		Item[2].Load(L"resource/item/item1.bmp");
		Item[3].Load(L"resource/item/item2.bmp");
		Item[4].Load(L"resource/item/item3.bmp");
		Item[5].Load(L"resource/item/item4.bmp");
		ChangeBox = -2;
		PickBox = false;

		Init();
		return 0;

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		HDC memdc = CreateCompatibleDC(hdc);
		HBITMAP membit = CreateCompatibleBitmap(hdc, WINSIZE_W, WINSIZE_H);
		SelectObject(memdc, membit);

		Render(memdc);

		BitBlt(hdc, 0, 0, WINSIZE_W, WINSIZE_H, memdc, 0, 0, SRCCOPY);

		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(hwnd, &ps);
	}
		return 0;

	case WM_MOUSEMOVE:
		GetCursorPos(&mouse);
		ScreenToClient(hwnd, &mouse);

		InvalidateRect(hwnd, NULL, FALSE);  // WM_PAINT 메시지 발생 
		break;
	case WM_LBUTTONDOWN: 
		if (SaveClick(mouse) != -1)
		{
			Save(SaveClick(mouse));
		}

		if (LoadClick(mouse) != -1)
		{
			Load(LoadClick(mouse));
		}
		
		if (BoxClick(mouse) != -1)
		{
			ChangeBox = BoxClick(mouse) - 1;
			PickBox = true;
		}

		if (PauseClick(mouse) == 1)
		{
			if (Pause == 1)
			{
				Pause = 0;
			}

			else
			{
				Pause = 1;
			}
		}

		if (SceneNum == MAPTOOL && PickBox)
		{
			Idx[0] = MousePosToIndex(mouse)[0];
			Idx[1] = MousePosToIndex(mouse)[1];
			if(Idx[0] != -1 && Idx[1] != -1)
				TileChangeInfo(Idx[0], Idx[1], ChangeBox);
		}
		break; 

	case WM_RBUTTONDOWN:
		if (SceneNum == MAPTOOL)
		{
			PickBox = false;
		}
		break;

	case WM_TIMER:
	
			switch (wParam)
			{
			case 1:
				Input();
				if (Pause == 1)
				{
				Update();
				}
				break;

			default:
				break;
			}
			InvalidateRect(hwnd, NULL, FALSE);  // WM_PAINT 메시지 발생 
		break;

	case WM_KEYDOWN:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SaveLoadButtonRender(HDC hdc)
{
	TCHAR str[128] = {};
	int x, y;

	for (int i = 0; i < 3; ++i)
	{
		Rectangle(hdc, SaveRC[i].left, SaveRC[i].top, SaveRC[i].right, SaveRC[i].bottom);
		x = SaveRC[i].left + 30;
		y = SaveRC[i].top + 10;
		wsprintf(str, L"Stage%d Save", i + 1);
		TextOut(hdc, x, y, str, lstrlen(str));

		Rectangle(hdc, LoadRC[i].left, LoadRC[i].top, LoadRC[i].right, LoadRC[i].bottom);
		x = LoadRC[i].left + 30;
		y = LoadRC[i].top + 10;
		wsprintf(str, L"Stage%d Load", i + 1);
		TextOut(hdc, x, y, str, lstrlen(str));
	}
}

// 맵초기화코드 
void TileClear()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j].rc = { -BLANK_X + j * 40, i * 40, -BLANK_X + (j + 1) * 40, (i + 1) * 40 };
			Tile[i][j].Break = true;			// 깨질수있는지 ex) 박스0 박스1 박스2 물풍선에 터지는데 그것들이은  true
			Tile[i][j].Move = true;				// 이 인덱스 타일위를 움직일 수 있는지 -> 충돌체크할때 쓸것
			Tile[i][j].Push = false;			// 밀수있는 박스 ex) 박스0 나무박스자너 그거임 ㅇㅇ
			Tile[i][j].ImageNum = -1;			
			Tile[i][j].Item = -1;				// 랜덤으로 아이템 뽑아내기위한건데 -1이면 아이템 X 0이면 스피드 등등 이렇게
			Tile[i][j].IndexX = j;				// 이거는 인덱스 저장
			Tile[i][j].IndexY = i;
		}
	}
}

void TileRectangleRender(HDC hdc)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (SceneNum == MAPTOOL)
			{
				MoveToEx(hdc, Tile[i][j].rc.left, Tile[i][j].rc.top, NULL);
				LineTo(hdc, Tile[i][j].rc.right, Tile[i][j].rc.top);
				LineTo(hdc, Tile[i][j].rc.right, Tile[i][j].rc.bottom);
				LineTo(hdc, Tile[i][j].rc.left, Tile[i][j].rc.bottom);
				LineTo(hdc, Tile[i][j].rc.left, Tile[i][j].rc.top);
			}

			if (Tile[i][j].ImageNum == -1)
			{
				BoxImage[0].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
			}
			if (Tile[i][j].ImageNum == 0)
			{
				BoxImage[1].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
			}
			if (Tile[i][j].ImageNum == 1)
			{
				BoxImage[2].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
			}
			if (Tile[i][j].ImageNum == 2)
			{
				BoxImage[3].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
			}
			if (Tile[i][j].ImageNum == 3)
			{
#ifdef _DEBUG
				BoxImage[4].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
#else
				BoxImage[0].TransparentBlt(hdc, Tile[i][j].rc, RGB(255, 0, 255));
#endif // _DEBUG

			}
		}
	}
}

void TileChangeInfo(int x, int y, int num)
{
	Tile[y][x].ImageNum = num;

	switch (num)
	{
	case -1:
		Tile[y][x].Move = true;
		Tile[y][x].Break = false;
		Tile[y][x].Push = false;
		Tile[y][x].Item = -1;

		break;
	case 0:
		Tile[y][x].Move = false;
		Tile[y][x].Break = true;
		Tile[y][x].Push = true;
		Tile[y][x].Item = rand() % ITEMRATE;
		
		break;
	case 1:
		Tile[y][x].Move = false;
		Tile[y][x].Break = true;
		Tile[y][x].Push = false;
		Tile[y][x].Item = rand() % ITEMRATE;

		break;
	case 2:
		Tile[y][x].Move = false;
		Tile[y][x].Break = true;
		Tile[y][x].Push = false;
		Tile[y][x].Item = rand() % ITEMRATE;

		break;

	case 3:
		Tile[y][x].Move = false;
		Tile[y][x].Break = false;
		Tile[y][x].Push = false;
		Tile[y][x].Item = -1;
		break;

	default:
		break;
	}

	if (Tile[y][x].Item > 4)
	{
		Tile[y][x].Item = -1;
	}
}

void MousePos(HDC hdc)
{
	static TCHAR str[128] = {};
	wsprintf(str, L"%d  %d", mouse.x, mouse.y);
	TextOut(hdc, 700, 0, str, lstrlen(str));
	int x, y;
	//x = (mouse.x - BLANK_X) / 40;
	//y = (mouse.y - BLANK_Y) / 40;
	x = (mouse.x + BLANK_X) / 40;
	y = mouse.y / 40;
	wsprintf(str, L"%d  %d", x, y);
	TextOut(hdc, 700, 30, str, lstrlen(str));
}

void TileBreak(int x, int y)
{
	Tile[y][x].Move = true;
	Tile[y][x].Break = false;
	Tile[y][x].Push = false;
	Tile[y][x].ImageNum = -1;
}

void TileBreak(vector<POINT> idx)
{
	for (int i = 0; i < idx.size(); ++i)
	{
		int x, y;
		x = idx[i].x;
		y = idx[i].y;
		if (Tile[y][x].ImageNum != 3)
		{
			TileBreak(x, y);
		}
	}
}

void TileUpdate()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Tile[i][j] = Bazzi.GetTileInfo(j, i);
			Tile[i][j] = Dao.GetTileInfo(j, i);
		}
	}
}

void BoxButtonRender(HDC hdc)
{
	for (int i = 0; i < BOXNUM; ++i)
	{
		BoxImage[i].TransparentBlt(hdc, BoxRC[i], RGB(255, 0, 255));
		static TCHAR str[128] = {};
		wsprintf(str, L"%d", i);
		TextOut(hdc, BoxRC[i].left, BoxRC[i].top, str, lstrlen(str));
	}
}

void ItemRender(HDC hdc)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			if (!Tile[i][j].Break)						// 타일이 깨지면 Tile.Break = false로 바뀌는데 그때 아이템을 그린다.
			{
				//Item[i][j].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				if (Tile[i][j].Item == -1)
				{
					Item[0].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

				if (Tile[i][j].Item == 0)
				{
					Item[1].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

				if (Tile[i][j].Item == 1)
				{
					Item[2].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

				if (Tile[i][j].Item == 2)
				{
					Item[3].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

				if (Tile[i][j].Item == 3)
				{
					Item[4].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

				if (Tile[i][j].Item == 4)
				{
					Item[5].TransparentBlt(hdc, Tile[i][j].rc, RGB(0, 255, 0));
				}

			}
		}
	}
}

int SaveClick(POINT mouse)
{
	for (int i = 0; i < 3; ++i)
	{
		if (PtInRect(&SaveRC[i], mouse))
		{
			return i;
		}
	}

	return -1;
}

int LoadClick(POINT mouse)
{
	for (int i = 0; i < 3; ++i)
	{
		if (PtInRect(&LoadRC[i], mouse))
		{
			return i;
		}
	}

	return -1;
}

int BoxClick(POINT mouse)
{
	for (int i = 0; i < BOXNUM; ++i)
	{
		if (PtInRect(&BoxRC[i], mouse))
		{
			return i;
		}
	}

	return -1;
}

int PauseClick(POINT mouse)
{
	if (PtInRect(&PauseRC, mouse))
	{
		int  a = 0;
		return 1;
	}

	return 0;
}

int * MousePosToIndex(POINT mouse)
{
	int idx[2] = { -1, -1 };

	if(mouse.x >= -BLANK_X && mouse.x <= 40 * TILEX - BLANK_X &&
		mouse.y >= 0 && mouse.y <= 40 * TILEY)
	{
		idx[0] = (mouse.x + BLANK_X) / 40;
		idx[1] = mouse.y / 40;
	}

	return idx;
}

// main 
void Init()
{
	// LOGO
	Logo.Init(L"resource/title/Title_Bg.bmp", { 0, 0, WINSIZE_W, WINSIZE_H }, "resource/bgm/1.mp3", 1);
	LogoButton.Init(L"resource/title/Title_Button_Start.bmp", 2, { 305, 427, 192, 55 }, { 0, 0, 192, 55 });

	// LOBBY
	Lobby.Init(L"resource/lobby/Lobby_Bg.bmp", { 0, 0, WINSIZE_W, WINSIZE_H }, "resource/bgm/2.mp3", 1);
	LobbyButton.Init(L"resource/lobby/Lobby_Button_Start.bmp", 2,
	{ 500, 485, 192, 55 }, { 0, 0, 192, 55 });
	StageButton[0].Init(L"resource/lobby/SelectMap1.bmp", STAGE1, { 630, 338, 135, 21 }, { 0, 0, 135, 21 });
	StageButton[1].Init(L"resource/lobby/SelectMap2.bmp", STAGE2, { 630, 359, 135, 21 }, { 0, 0, 135, 21 });
	StageButton[2].Init(L"resource/lobby/SelectMap3.bmp", STAGE3, { 630, 379, 135, 21 }, { 0, 0, 135, 21 });

	// STAGE
	int FrameCnt[] = { 5, 5, 4, 4 };
	Bazzi.Init(L"resource/character/Bazzi.bmp", FrameCnt, 1, 1, BAZZI);
	Dao.Init(L"resource/character/Dao.bmp", FrameCnt, 15, 13, DAO);
	Stage1_BK.Init(L"resource/map/InGame_Bg.bmp", { 0, 0, WINSIZE_W, WINSIZE_H }, "resource/bgm/3.mp3", 1);
	ToLobbyButton.Init(L"resource/map/Exit.bmp", 2, { 647, 561, 140, 32 }, { 0, 0, 140, 32 });

	srand(size_t(time(NULL)));
}

void Update()
{
	if (SceneNum == INGAME)
	{
		if (StageNum == LOGO)
		{
			Lobby.BGMOnOff(false);
			Stage1_BK.BGMOnOff(false);
			LogoButton.Update();
			if (LogoButton.GetClick())
			{
				LogoButton.SetClick(false);
				StageNum = LOBBY;
				Lobby.BGMOnOff(true);
				Logo.BGMOnOff(false);
			}
		}

		else if (StageNum == LOBBY)
		{
			Logo.BGMOnOff(false);
			Stage1_BK.BGMOnOff(false);
			LobbyButton.Update();
			if (LobbyButton.GetClick())
			{
				LobbyButton.SetClick(false);
				StageNum = StageChoice;
				Stage1_BK.BGMOnOff(true);

				Lobby.BGMOnOff(false);
			}
		}

		else 
		{
			Stage1_BK.BGMOnOff(true);
			Logo.BGMOnOff(false);
			Lobby.BGMOnOff(false);
			if (StageNum == STAGE1)
			{
				if (!LoadStage[STAGE1])
				{
					Load(STAGE1);
					int FrameCnt[] = { 5, 5, 4, 4 };
					Init();

					LoadStage[STAGE1] = true;
				}
				Bazzi.SetTileInfo(Tile);
				Dao.SetTileInfo(Tile);
				TileBreak(Bazzi.GetBubbleBreakIndex());
				TileBreak(Dao.GetBubbleBreakIndex());
				Bazzi.BubbleIdxClear();
				Dao.BubbleIdxClear();
			}

			else if (StageNum == STAGE2)
			{
				if (!LoadStage[STAGE2])
				{
					Load(STAGE2);
					int FrameCnt[] = { 5, 5, 4, 4 };
					Init();

					LoadStage[STAGE2] = true;
				}
				Bazzi.SetTileInfo(Tile);
				Dao.SetTileInfo(Tile);
				TileBreak(Bazzi.GetBubbleBreakIndex());
				TileBreak(Dao.GetBubbleBreakIndex());
				Bazzi.BubbleIdxClear();
				Dao.BubbleIdxClear();
			}
			else if (StageNum == STAGE3)
			{
				if (!LoadStage[STAGE3])
				{
					Load(STAGE3);
					int FrameCnt[] = { 5, 5, 4, 4 };
					Init();
					LoadStage[STAGE3] = true;
				}
				Bazzi.SetTileInfo(Tile);
				Dao.SetTileInfo(Tile);
				TileBreak(Bazzi.GetBubbleBreakIndex());
				TileBreak(Dao.GetBubbleBreakIndex());
				Bazzi.BubbleIdxClear();
				Dao.BubbleIdxClear();
			}
			ToLobbyButton.Update();
			if (ToLobbyButton.GetClick())
			{
				ToLobbyButton.SetClick(false);
				StageNum = LOBBY;
			}
			Bazzi.Update();
			Dao.Update();
		}
	}
}

void Input()
{
	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		SceneNum = MAPTOOL;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		SceneNum = INGAME;
		StageNum = LOGO;
		Logo.BGMOnOff(true);
	}
	
	if (GetAsyncKeyState(VK_F3) & 0x8000)
	{
		StageNum = STAGE1;
		LoadStage[STAGE1] = false;
	}

	if (GetAsyncKeyState(VK_F4) & 0x8000)
	{
		StageNum = STAGE2;
		LoadStage[STAGE2] = false;
	}

	if (GetAsyncKeyState(VK_F6) & 0x8000)
	{
		StageNum = STAGE3;
		LoadStage[STAGE3] = false;
	}

	if (KEYDOWN(VK_LBUTTON))
	{
		
	}

	if (SceneNum == INGAME)
	{
		if (StageNum == LOGO)
		{
			LogoButton.SetMousePos(mouse);
			LogoButton.Input();
		}

		else if (StageNum == LOBBY)
		{
			LobbyButton.SetMousePos(mouse);
			LobbyButton.Input();
			for (int i = 0; i < 3; ++i)
			{
				StageButton[i].SetMousePos(mouse);
				StageButton[i].Input();
			}
		}

		else 
		{
			ToLobbyButton.SetMousePos(mouse);
			ToLobbyButton.Input();
			Bazzi.Input();
			Dao.Input();
		}
	}
}

void Render(HDC hdc)
{
	if (SceneNum == MAPTOOL)
	{
		Stage1_BK.Render(hdc);
		SaveLoadButtonRender(hdc);
		BoxButtonRender(hdc);
		TileRectangleRender(hdc);
		MousePos(hdc);
	}

	else if (SceneNum == INGAME)
	{
		if (StageNum == LOGO)
		{
			Logo.Render(hdc);
			LogoButton.Render(hdc);
		}

		else if (StageNum == LOBBY)
		{
			Lobby.Render(hdc);
			LobbyButton.Render(hdc);

			for (int i = 0; i < 3; ++i)
			{
				if (StageButton[i].GetClick())
				{
					StageChoice = i;
					StageButton[i].Render(hdc);
				}
								
			}
		}

		else if (StageNum == STAGE1)
		{
			Stage1_BK.Render(hdc);
			TileRectangleRender(hdc);
			ItemRender(hdc);
			ToLobbyButton.Render(hdc);
			Bazzi.Render(hdc);
			Dao.Render(hdc);
		}

		else if (StageNum == STAGE2)
		{
			Stage1_BK.Render(hdc);
			TileRectangleRender(hdc);
			ItemRender(hdc);
			ToLobbyButton.Render(hdc);
			Bazzi.Render(hdc);
			Dao.Render(hdc);
		}

		else if (StageNum == STAGE3)
		{
			Stage1_BK.Render(hdc);
			TileRectangleRender(hdc);
			ItemRender(hdc);
			ToLobbyButton.Render(hdc);
			Bazzi.Render(hdc);
			Dao.Render(hdc);
		}
	}
}

void Save(int num)
{
	string FileName = "Stage";
	string Num = to_string(num);
	string Data = ".txt";

	FileName += Num;
	FileName += Data;

	FILE* pFile = NULL;

	fopen_s(&pFile, FileName.c_str(), "wb");

	if (!pFile)
		return;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fwrite(&Tile[i][j], sizeof(TILEINFO), 1, pFile);
		}
	}

	fclose(pFile);
}

void Load(int num)
{
	string FileName = "Stage";
	string Num = to_string(num);
	string Data = ".txt";

	FileName += Num;
	FileName += Data;

	FILE* pFile = NULL;

	fopen_s(&pFile, FileName.c_str(), "rb");

	if (!pFile)
		return;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fread(&Tile[i][j], sizeof(TILEINFO), 1, pFile);
			TileChangeInfo(j, i, Tile[i][j].ImageNum);
		}
	}

	fclose(pFile);

	Bazzi.SetTileInfo(Tile);
	Dao.SetTileInfo(Tile);

}

void SetTile(int x, int y, int item)
{
	Tile[y][x].Item = item;
}
