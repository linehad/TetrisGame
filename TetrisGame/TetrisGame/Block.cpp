#include <iostream>
#include <Windows.h>
#include "Block.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;
Block::Block()
{
	blockPosition = 0;
	x = 5, y = 4;
	saveLeftX = 0, saveRightX = 0;
	lastX = 0;

	saveBlock.resize(4, std::vector<int>(4, 0));
	block.resize(4, std::vector<int>(4, 0));
	m_GameBoard = NULL;
	m_Player = NULL;
}

// 이동중인 모든 블럭을 지우는 함수
void Block::ReMoveBlock()
{
	// 맵 스캔
	for (int i = 2; i < 22; i++)
	{
		for (int j = 2; j < 12; j++)
		{
			if (m_GameBoard->board[i][j] == 1)
			{
				m_GameBoard->board[i][j] = 0;
			}
		}
	}
}

// 블럭 객체를 돌리는 함수
void Block::RotateBlock()
{
	copy(block.begin(), block.end(), saveBlock.begin());

	// 블럭 회전
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[j][i] = saveBlock[3 - i][j];
		}
	}
}

// 돌려진 블럭 객체를 게임보드에 반영하는 함수
void Block::RotateBlockSave()
{
	RotateBlock();
	ReMoveBlock();

	m_Player->touchLeftWall = false;
	m_Player->touchRightWall = false;

	bool flag = false;
	const int WALL = 103;
	int ty = y;

	int indexY = 3; // 블럭 오브젝트 0번째 부터 좌에서 우로 올라가면서 탐색
	int lastLX = 12, lastRX = 2; // x가 맵 바깥으로 나갔는지 확인하는 변수

	// x, y 좌표 좌에서 우로 아래에서 위로 4*4 스캔
	for (int i = 0; i < 4; i++)
	{
		int indexX = 0; // 블럭 오브젝트의 X좌표
		int tx = x; // board의 x좌표
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			// count가 3이 되면 j가 4번 돌동안 블록내부에 아무것도 없었단 말이므로 ty의 위치를 현상유지.
			if (count == 3)
			{
				ty++;
			}
			// 블럭이 들어 있다면 board을 1로 채우고 lastLX와 Rx를 갱신한다.
			if (block[indexY][indexX] == 1)
			{
				// 회전 반경에 놓아진 블럭이 있으면 취소
				if (m_GameBoard->board[ty][tx] == 2)
				{
					ReMoveBlock();
					copy(saveBlock.begin(), saveBlock.end(), block.begin());
					copy(m_GameBoard->saveBoard.begin(), m_GameBoard->saveBoard.end(), m_GameBoard->board.begin());
					y = saveY;
					return;
				}
				m_GameBoard->board[ty][tx] = 1;
				lastLX = lastLX > tx ? tx : lastLX; // 따라오는 왼쪽 좌표가 tx보다 크면 tx로 바꿔줌(항상 작아야함)
				lastRX = lastRX < tx ? tx : lastRX;  // 오른쪽 좌표는 항상 커야함
			}
			// 블럭이 없다면 count를 1 올린다.
			else if (block[indexY][indexX] == 0) count++;
			tx++;
			indexX++;
		}
		ty--;
		indexY--;
	}

	// x 범위 초과시 예외처리
	if (lastRX > 11)
	{
		m_Player->MoveLeft();
	}

	else if (lastLX <  2)
	{
		m_Player->MoveRight();
	}
}

// 블럭을 생성하고 게임오버를 판별하는 함수
void Block::CreateBlock()
{
	m_Player->touchLeftWall = false;
	m_Player->touchRightWall = false;

	x = 5, y = 5;
	ReMoveBlock();

	srand((unsigned int)time(NULL));
	int randBlock = rand() % 7;

 	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			block[i][j] = 0;


	switch (randBlock)
	{
	case 0: // 1자 블럭
		block[1][0] = 1;
		block[1][1] = 1;
		block[1][2] = 1;
		block[1][3] = 1;
		break;

	case 1: //ㄱ자 블럭
		block[1][1] = 1;
		block[1][2] = 1;
		block[2][2] = 1;
		block[3][2] = 1;
		break;

	case 2: // 역 ㄱ자 블럭
		block[1][1] = 1;
		block[1][2] = 1;
		block[2][1] = 1;
		block[3][1] = 1;
		break;

	case 3: // Z자 블럭
		block[1][0] = 1;
		block[1][1] = 1;
		block[2][1] = 1;
		block[2][2] = 1;
		break;

	case 4: // 역 Z자 블럭
		block[1][1] = 1;
		block[1][2] = 1;
		block[2][0] = 1;
		block[2][1] = 1;
		break;

	case 5: // 네모블럭
		block[1][1] = 1;
		block[1][2] = 1;
		block[2][1] = 1;
		block[2][2] = 1;
		break;

	case 6: // ㅗ자 블럭
		block[1][1] = 1;
		block[2][0] = 1;
		block[2][1] = 1;
		block[2][2] = 1;
		break;

	default:
		break;
	}

	int tx = x;

	int indexY = 3; // 블럭 오브젝트가 처음 생성될 때 맨 윗줄에는 아무것도 없다

	
	for (int i = 4; i > 1; i--)
	{
		int indexX = 0;
		for (int j = tx; j < tx + 4; j++)
		{
			// 더이상 블럭이 생성 불가능 하다면
			if (block[indexY][indexX] == 1 && m_GameBoard->board[i][j] == 2)
			{
				b_gameOver = true;
				return;
			}
			// 블럭이 들어 있다면 생성
			else if (block[indexY][indexX] == 1)
			{
				m_GameBoard->board[i][j] = 1;
			}
			indexX++;
		}
		indexY--;
	}
	saveRightX = 8;
	saveLeftX = 5;
}

void  Block::Link(GameBoard* GameBoardOB, Player* PlayerOB)
{
	m_GameBoard = GameBoardOB;
	m_Player = PlayerOB;
}