#include <conio.h>
#include "Player.h"
#include "Block.h"
#include "GameBoard.h"

using namespace std;

Player::Player()
{
	acceleration = 1; // 가속도가 1 증가 할때마다 비트연산은 2 제곱씩 들어감
	m_block = NULL;
	m_GameBoard = NULL;
}

void Player::MoveLeft()
{
	if (touchLeftWall)
	{
		return;
	}

	std::vector<std::vector<int>> backupBoard(24, std::vector<int>(14, 0));
	copy(m_GameBoard->board.begin(), m_GameBoard->board.end(), backupBoard.begin());

	touchRightWall = false;

	const int WALL = 103;

	// x, y 좌표 4*4 왼쪽에서 오른쪽으로 세로 부터 스캔
	int trX = m_block->saveRightX;
	int tlX = m_block->saveLeftX;

	int ty = m_block->y;

	m_block->lastX = 12;
	for (int i = tlX; i <= trX; i++)
	{
			for (int j = ty; j > ty - 4 ; j--)
		{
			// 현재 좌표에 블럭이 들어 있다면
			if (m_GameBoard->board[j][i] == 1)
			{
				// 블럭이 들어 있는 현재 x 좌표가 마지막으로 저장된 x좌표보다 작다면 값을 바꾼다.
				if (m_block->lastX > i)
				{
					m_block->lastX = i;
				}
				// 마지막으로 저장된 좌표로 부터 왼쪽이 벽이라면 또는 이미 놓아진 블럭이라면 취소
				if (m_GameBoard->board[j][m_block->lastX - 1] == WALL || (m_GameBoard->board[j][i] == 1 && m_GameBoard->board[j][i - 1] == 2))
				{
					copy(backupBoard.begin(), backupBoard.end(), m_GameBoard->board.begin());
					touchLeftWall = true;
					return;
				}

				// 현재 좌표에 1이 들어 있고 왼쪽이 벽이 아니라면
				else
				{
					m_GameBoard->board[j][i] = 0;
					m_GameBoard->board[j][i - 1] = 1;
				}
			}
		}
	}

	// 저장된 왼쪽 X값이 2보다 작다면 재보정
	if (m_block->saveLeftX < 2)
	{
		m_block->x = 2;
		m_block->saveLeftX = 2;
		m_block->saveRightX = 5;
	}
	else
	{
		m_block->x--;
		m_block->saveLeftX--;
		m_block->saveRightX--;
	}
}

void Player::MoveRight()
{
	if (touchRightWall)
	{
		return;
	}

	std::vector<std::vector<int>> backupBoard(24, std::vector<int>(14, 0));
	copy(m_GameBoard->board.begin(), m_GameBoard->board.end(), backupBoard.begin());

	int trX = m_block->saveRightX;
	int tlX = m_block->saveLeftX;
	int ty = m_block->y;
	touchLeftWall = false;

	const int WALL = 103;

	// x, y 좌표 4*4 오른쪽에서 왼쪽으로 세로 부터 스캔
	m_block->lastX = 1;
	// 저장된 x의 오른쪽 4번째 칸부터 아래부터 위로 스캔
	for (int i = trX; i >= tlX; i--)
	{
		for (int j = ty; j > ty - 4; j--)
		{
			// 현재 좌표에 블럭이 들어 있다면
			if (m_GameBoard->board[j][i] == 1)
			{
				// 블럭이 들어 있는 현재 x 좌표가 마지막으로 저장된 x좌표보다 크다면 값을 바꾼다.
				if (m_block->lastX < i)
				{
					m_block->lastX = i;
				}
				// 마지막으로 저장된 좌표로 부터 오른쪽이 벽이라면 또는 블럭이라면 취소
				if (m_GameBoard->board[j][m_block->lastX + 1] == WALL || (m_GameBoard->board[j][i] == 1 && m_GameBoard->board[j][i + 1] == 2))
				{
					copy(backupBoard.begin(), backupBoard.end(), m_GameBoard->board.begin());
					touchRightWall = true;
					return;
				}

				// 현재 좌표에 1이 들어 있고 오른쪽이 벽이 아니라면
				else
				{
					m_GameBoard->board[j][i] = 0;
					m_GameBoard->board[j][i + 1] = 1;
				}
			}
		}
	}

	// 저장된 오른쪽 X값이 12보다 크다면 재보정
	if (m_block->saveRightX > 12)
	{
		m_block->x = 9;
		m_block->saveLeftX = 9;
		m_block->saveRightX = 12;
	}

	else
	{
		m_block->x++;
		m_block->saveLeftX++;
		m_block->saveRightX++;
	}
}

void Player::MoveDown()
{
	touchLeftWall = false;
	touchRightWall = false;

	if (touchBottom)
	{
		touchBottom = false;
		m_block->CreateBlock();
		return;
	}
	const int BOTTOM = 102;

	int lastY = 1;
	bool flag = false;

	int trX = (m_block->saveRightX) > 21 ? 21 : (m_block->saveRightX); 	// 블럭 0, 3의 좌표
	int tlX = (m_block->saveLeftX) > 18 ? 18 : (m_block->saveLeftX);   // 블럭 0, 0의 좌표

	if (m_block->y > 21)
	{
		m_block->y = 21;
	}

	int ty = m_block->y; // y의 현재 좌표 시작 값 1 y는 1증가 됐으나 스캔은 한칸 위에서 시작해야함

	int count = 0;
	vector<int>savetx;
	vector<int>savety;

	// x, y 좌표 4*4 아래쪽에서 위쪽으로 완쪽에서 오른쪽으로 가로 부터 스캔
	for (int i = ty; i > ty - 4; i--)
	{
		for (int j = tlX; j <= trX; j++)
		{
			// 현재 좌표에 블럭이 들어 있다면
			if (m_GameBoard->board[i][j] == 1)
			{
				// 블럭이 들어 있는 현재 y 좌표가 마지막으로 저장된 y좌표보다 크다면 값을 바꾼다.
				if (lastY < i)
				{
					lastY = i;
				}
				// 마지막으로 저장된 좌표로 부터 아래가 바닥 또는 블럭 아래쪽이 이미 놓아진 벽돌이라면
				if (m_GameBoard->board[lastY + 1][j] == BOTTOM || (m_GameBoard->board[i][j] == 1 && m_GameBoard->board[i + 1][j] == 2))
				{
					touchBottom = true; // 바닥 터치!

					// 바닥부터 위쪽으로 훓어본다.
					for (int k = lastY; k >= lastY - 3; k--)
					{
						for (int l = tlX; l <= trX; l++)
						{
							// 해당 값이 1이라면 (이미 놓아진 벽돌로)2로 상태 변환
							if (m_GameBoard->board[k][l] == 1)
							{
								m_GameBoard->board[k][l] = 2;
							}
						}
					}
					flag = true;
					break;
				}

				// 현재 좌표에 1이 들어 있고 아래가 바닥이 아니라면 카운트 증가
				else
				{
					count++;
					// x,y 좌표를 임시저장
					savetx.push_back(j);
					savety.push_back(i);
					// count는 모든 블럭을 살펴보기 위함
					if (count == 4)
					{
						// 모든 블럭이 조건을 만족하면 한칸 내림
						for (int k = 0; k < 4; k++)
						{
							m_GameBoard->board[savety[k]][savetx[k]] = 0;
							m_GameBoard->board[savety[k] + 1][savetx[k]] = 1;

						}
					}
				}
			}
		}
		if (flag) break;
	}
	m_block->saveY = m_block->y; // ty 저장
	copy(m_GameBoard->board.begin(), m_GameBoard->board.end(), m_GameBoard->saveBoard.begin());
	m_block->y++;
}

void Player::MoveBlock()
{
	// 회전이 너무 빠르게 일어남으로 예외처리
	if (_kbhit())
	{
		int key = _getch();
		if (key == 224)
		{
			key = _getch();
		}

		switch (key)
		{
		case 72: //위
			if (m_block->y == 22) break;
			m_block->RotateBlockSave();
			break;
			/*
		case 75: //왼쪽
			MoveLeft();
			break;
		case 77: //오른쪽
			MoveRight();
			break;
		case 80: //아래
			int temp = acceleration;
			acceleration = temp + 10;
			MoveDown();
			acceleration = temp;
			break;*/
		}
	}
	Sleep(50);
	if ((GetKeyState(VK_DOWN) & 0x8000))
	{
		int temp = acceleration;
		acceleration = temp + 10;
		MoveDown();
		acceleration = temp;
	}
	else if ((GetKeyState(VK_LEFT) & 0x8000))
	{
		MoveLeft();
	}
	else if ((GetKeyState(VK_RIGHT) & 0x8000))
	{
		MoveRight();
	}
}

Block Player::GetBlock()
{
	return *m_block;
}

GameBoard* Player::GetGameBoard()
{
	return m_GameBoard;
}

void Player::Link(GameBoard* GameBoardOb, Block* blockOb)
{
	m_block = blockOb;
	m_GameBoard = GameBoardOb;
}