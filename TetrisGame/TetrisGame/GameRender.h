#pragma once
#include "Player.h"
#include "GameBoard.h"
#include "Block.h"

class GameRender
{
private:
	Player m_player;
	GameBoard m_gameBoard;
	Block m_block;

	int gameSpeed;

	unsigned long long startTick;
	unsigned long long speedLevelTick;
	unsigned long long moveTick;

	void BlockDropSpeed();
	void GameOver();
public:

	GameRender();
	GameRender(Player& player);
	~GameRender();

	bool b_runTetris = true;

	void GameStart();
	void BlockControl();
};