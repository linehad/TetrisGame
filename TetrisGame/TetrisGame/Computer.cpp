#include <vector>
#include <cstdlib>
#include "Computer.h"
#include "ComputerGameBoard.h"
#include "Player.h"
#include "Block.h"
#include "GameBoard.h"

using namespace std;

Computer::Computer()
{
	Tick = GetTickCount64();
}

void Computer::HightLineHoleBump()
{
	float bestScore = NULL;
	count = 0;

	float aggregateHeight = -0.510066f;
	float completeLines = 0.760666f;
	float holes = -0.35663f;
	float bumpiness = -0.184483f;

	ComputerGameBoard* m_GameBoard = (ComputerGameBoard*)GetGameBoard();
	Block m_block = GetBlock();
	Player player;

	for (int rotation = 0; rotation < 4; rotation++)
	{
		int num = 0;
		moveBlock.clear();
		ComputerGameBoard temp = *m_GameBoard;
		Block block = m_block;
		player.Link(&temp, &block);
		block.Link(&temp, &player);
		for (int i = 0; i < rotation; i++)
		{
			block.RotateBlockSave();
		}

		if (block.cantRotate)
			break;

		while (!player.touchLeftWall)
		{
			player.MoveLeft();
			num--;
			if (num < -5)
				break;
		}
		player.touchLeftWall = false;
		num++;

		while (!player.touchRightWall)
		{
			Block _block = block;
			ComputerGameBoard _temp = temp;
			player.Link(&_temp, &_block);
			_block.Link(&_temp, &player);
			while (!player.touchBottom)
			{
				player.MoveDown();
			}
			player.touchBottom = false;

			float score = NULL;

			score =
				(aggregateHeight * _temp.AggregateHeight()) +
				(completeLines * _temp.CompleteLines()) +
				(holes * _temp.Holes()) +
				(bumpiness * _temp.Bumpiness());

			if (score > bestScore || bestScore == NULL)
			{
				bestScore = score;
				LRNum = num;
				rotNum = rotation;
			}

			player.Link(&temp, &block);
			block.Link(&temp, &player);
			player.MoveRight();
			num++;
			if (num > 5)
				break;
		}
		player.touchRightWall = false;
		num--;
	}

	//moveBlock.push_back(4);//Down

	for (int i = 0; i < rotNum; i++)
	{
		moveBlock.push_back(3);//Rotate
	}
	if (LRNum > 0)
	{
		for (int i = 0; i < LRNum; i++)
		{
			moveBlock.push_back(2);//Right
		}
	}
	else
	{
		for (int i = 0; i < -LRNum; i++)
		{
			moveBlock.push_back(1);//Left
		}
	}
}

void Computer::MoveBlock()
{
	if (GetTickCount64() - Tick >= 200)
	{
		if (moveBlock.size() <= count)
		{
			if (!touchBottom)
				MoveDown();
		}
		else
		{
			Block* block = Player::m_block;
			switch (moveBlock[count])
			{
			case 1:
				MoveLeft();
				break;
			case 2:
				MoveRight();
				break;
			case 3:
				block->RotateBlockSave();
				break;
			case 4:
				MoveDown();
				break;
			default:
				break;
			}
			count++;
		}
		Tick = GetTickCount64();
	}
}
