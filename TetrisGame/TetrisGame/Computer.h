#pragma once
#include "Player.h"
#include "Block.h"
#include <vector>

using namespace std;

class Computer : public Player
{
private:
	vector<int> moveBlock;

	unsigned long long Tick;
public:
	int count = 0;
	int LRNum = 0;
	int rotNum = 0;

	Computer();
	void HightLineHoleBump();
	virtual void MoveBlock();
};