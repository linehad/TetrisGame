#pragma once

class Block;
class GameBoard;
class Player
{
private:
	Block* m_block;
	GameBoard* m_GameBoard;
public:

	int acceleration; // 가속도가 1 증가 할때마다 비트연산은 2 제곱씩 들어감

	bool touchLeftWall = false;
	bool touchRightWall = false;
	bool touchBottom = false;

	Player();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveBlock();

	void Link(GameBoard* GameBoardOb, Block* blockOb);
};