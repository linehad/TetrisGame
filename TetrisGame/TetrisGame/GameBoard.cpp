#include <iostream>
#include<conio.h>
#include "GameBoard.h"

static HANDLE g_hScreen[2]; // 번갈아가면서 출력 될 2개의 화면

GameBoard::GameBoard()
{	
	board.resize(24, std::vector<int>(14, 0)); // x = 2부터 11까지 y = 2 부터 21 까지 || 0, 1, 12 13 벽, 0, 1, 22, 23 벽
    saveBoard.resize(24, std::vector<int>(14, 0));
}

// 한줄이 다 차면 비워버림
void GameBoard::LineClear(int line)
{
    // 해당 라인 지움
	for (int i = 2; i < 12; i++)
	{
		board[line][i] = 0;
	}

    // 해당 라인 부터 위에 있는거 지움
	for (int i = line; i > 2; i--)
	{
		for (int j = 2; j < 12; j++)
		{
			board[i][j] = board[i - 1][j];
			board[i - 1][j] = 0;
		}
	}
}

// 재시작시 모든 블럭 지워버림
void GameBoard::ClearBoard()
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            board[i][j] = 0;
            saveBoard[i][j] = 0;
        }
    }
}

void GameBoard::ScreenInit()
{
    CONSOLE_CURSOR_INFO cci = { 0, };

    // 화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 커서를 숨긴다.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

// 출력 화면 전환
void GameBoard::ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

// cls의 커스터 마이징
void GameBoard::ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

// 빠르게 0과 1을 번갈아 가며 출력
void GameBoard::ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

// string에 출력할 모든것을 담는다. string의 내용을 콘솔에 출력하게 된다.
void GameBoard::ScreenPrint(short x, short y, std::string s)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], s.c_str(), s.size(), &dw, NULL);
}

// 1초 단위로 출력 직접적으로 출력하는 부분이다.
void GameBoard::Render()
{
    ScreenClear();
    std::string s;

    // 가로 그리기
    for (int j = 0; j < 14; j++)
    {
        // 위쪽 벽
        board[0][j] = 101;
        board[1][j] = 101;

        // 아래 벽
        board[22][j] = 102;
        board[23][j] = 102;
    }

    // 세로 그리기
    for (int j = 2; j < 22; j++)
    {
        // 왼쪽 벽
        board[j][0] = 103;
        board[j][1] = 103;


        // 오른쪽 벽
        board[j][12] = 103;
        board[j][13] = 103;
    }

    // (1, 1) 부터 (12, 22) 까지 스캔
    for (int i = 1; i < 23; i++)
    {
        lineClearCount = 0;
        for (int j = 1; j < 13; j++)
        {
            int temp = j;
            // 이미 쌓여진 블럭이라면
            if (board[i][j] == 101 || board[i][j] == 102 || board[i][j] == 103)
            {
                s += "▩";
            }

            else if (board[i][j] == 1)
            {
                s += "□";
            }
            else if (board[i][j] == 2)
            {
                s += "■";
                lineClearCount += 2;
                // 한줄이 다차면 라인 비우기
                if (lineClearCount == 20) LineClear(i);
            }
            else
            {
                s += "  ";
            }
        }
        s += '\n';
    }
    ScreenPrint(0, 0, s);
    ScreenFlipping();
}

// 게임 오버시 출력화면
void GameBoard::GameOver()
{
    ScreenClear();
    std::string s;

    // (1, 1) 부터 (12, 22) 까지 스캔
    for (int i = 1; i < 23; i++)
    {
        lineClearCount = 0;
        for (int j = 1; j < 13; j++)
        {
            int temp = j;
            // 이미 쌓여진 블럭이라면


            if (i == 10 && j == 4)
            {
                s += "**게임 오버**";
            }
            else if (i == 12 && j == 4)
            {
                s += "재시작 : R ";
            }
            else if (i == 13 && j == 4)
            {
                s += "게임 종료 : E S C";
            }
            else
            {
                s += "  ";
            }
        }
        s += '\n';
    }
    ScreenPrint(0, 0, s);
    ScreenFlipping();
}