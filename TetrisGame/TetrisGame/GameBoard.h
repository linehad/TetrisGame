#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>

class GameBoard
{
private:
	bool g_nScreenIndex = false;

public:
	int lineClearCount = 0;
	std::vector<std::vector<int>> board;
	std::vector<std::vector<int>> saveBoard;

	bool b_runTetris = true;

	GameBoard();
	void LineClear(int line);
	void ClearBoard();

	// 더블 버퍼링 관련 함수
	void ScreenInit();
	void ScreenFlipping();
	void ScreenClear();
	void ScreenRelease();
	void ScreenPrint(short x, short y, std::string s);
	void Render();

	void GameOver();
};