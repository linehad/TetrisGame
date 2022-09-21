#pragma once
#include <vector>

class GameBoard;
class Player;
class Block
{
private:
	GameBoard* m_GameBoard;
	Player* m_Player;

	std::vector<std::vector<int>> saveBlock;
public:
	bool b_gameOver = false;

	int blockPosition;
	int x, y;
	int saveLeftX, saveRightX;
	int lastX;
	int saveY = 0;

	std::vector<std::vector<int>> block;

	Block();
	void ReMoveBlock();
	void RotateBlockSave();
	void CreateBlock();
	void RotateBlock();

	void Link(GameBoard* GameBoardOB, Player* PlayerOB);
};