#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>

#include "GameRender.h"

GameRender::GameRender()
{
	m_player.Link(&m_gameBoard, &m_block);
	m_block.Link(&m_gameBoard, &m_player);
    startTick = GetTickCount64();
    speedLevelTick = GetTickCount64();
    moveTick = GetTickCount64();

    gameSpeed = 1 << m_player.acceleration;
}

GameRender::~GameRender()
{
	m_gameBoard.ScreenRelease();
}

// 블럭이 더이상 생성될 수 없을때 불려질 함수
void GameRender::GameOver()
{
    bool flag = true;
    int key;
    while (flag)
    {
        m_gameBoard.GameOver();
        if (_kbhit())
        {
            key = _getch();
            if (key == 83 || key == 114)
            {
                gameSpeed = 1;

                m_block.b_gameOver = false;
                m_gameBoard.ClearBoard();
                m_block.CreateBlock();
                m_gameBoard.Render();

                flag = !flag;
            }
            else if (key == 27)
            {
                b_runTetris = false;
                return;
            }
        }
    }
}

void GameRender::GameStart()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	m_gameBoard.ScreenInit();

	std::cout << "게임을 시작하려면 아무 키나 입력하세요\n";
	int temp = _getch();
	m_block.CreateBlock();
}

void GameRender::BlockControl()
{	
	b_runTetris = m_gameBoard.b_runTetris;
	if (m_block.y > 21)
	{
		m_block.y = 21;
	}
    else if (m_block.b_gameOver)
    {
        GameOver();
    }


    m_player.MoveBlock();

	BlockDropSpeed();


	m_gameBoard.Render();
}


void GameRender::BlockDropSpeed()
{
	m_gameBoard.ScreenInit();

    // 2000을 2의 제곱수로 비트연산한다. gameSpeed가 2일때 1000, 4일때 500... 으로 2배씩 속도가 증가하게 된다. 
    if (GetTickCount64() - startTick >= (2000 >> gameSpeed))
    {
        if (gameSpeed < 4 && GetTickCount64() - speedLevelTick >= 15000) // 15초 마다 스피드 증가
        {
            gameSpeed++;
            speedLevelTick = GetTickCount64(); // 블럭이 내려가는 속도 레벨
        }
        m_player.MoveDown();
        startTick = GetTickCount64(); // 블럭이 내려가는 속도용       
    }
}