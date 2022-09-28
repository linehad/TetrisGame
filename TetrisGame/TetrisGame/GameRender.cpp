#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>

#include "GameRender.h"

GameRender::GameRender()
{
    m_player = new Player();
    m_gameBoard = new GameBoard();
    m_block = new Block();
	m_player->Link(m_gameBoard, m_block);
	m_block->Link(m_gameBoard, m_player);
    startTick = GetTickCount64();
    speedLevelTick = GetTickCount64();
    moveTick = GetTickCount64();

    gameSpeed = 1 << m_player->acceleration;
}

GameRender::GameRender(Player& player, GameBoard& gameboard, Block& block)
    : m_player(&player), m_gameBoard(&gameboard), m_block(&block)
{
    m_player->Link(m_gameBoard, m_block);
    m_block->Link(m_gameBoard, m_player);
    startTick = GetTickCount64();
    speedLevelTick = GetTickCount64();
    moveTick = GetTickCount64();

    gameSpeed = 1 << m_player->acceleration;
}

GameRender::~GameRender()
{
	m_gameBoard->ScreenRelease();
}

// 블럭이 더이상 생성될 수 없을때 불려질 함수
void GameRender::GameOver()
{
    bool flag = true;
    int key;
    while (flag)
    {
        m_gameBoard->GameOver();
        if (_kbhit())
        {
            key = _getch();
            if (key == 83 || key == 114)
            {
                gameSpeed = 1;

                m_block->b_gameOver = false;
                m_gameBoard->ClearBoard();
                m_block->CreateBlock();
                m_gameBoard->Render();

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
	m_gameBoard->ScreenInit();

	std::cout << "게임 속도를 입력하세요(블럭이 1초당 n칸 떨어집니다) : ";
    std::cin >> gameSpeed;
	m_block->CreateBlock();
}

void GameRender::BlockControl()
{	
	b_runTetris = m_gameBoard->b_runTetris;
	if (m_block->y > 21)
	{
		m_block->y = 21;
	}
    else if (m_block->b_gameOver)
    {
        GameOver();
    }


    m_player->MoveBlock();

	BlockDropSpeed();


	m_gameBoard->Render();
}


void GameRender::BlockDropSpeed()
{
	m_gameBoard->ScreenInit();

    if (GetTickCount64() - startTick >= (1000 / gameSpeed))
    {
        if (gameSpeed < 30 && GetTickCount64() - speedLevelTick >= 15000) // 15초 마다 스피드 증가
        {
            gameSpeed++;
            speedLevelTick = GetTickCount64(); // 블럭이 내려가는 속도 레벨
        }
        m_player->MoveDown();
        startTick = GetTickCount64(); // 블럭이 내려가는 속도용       
    }
}
