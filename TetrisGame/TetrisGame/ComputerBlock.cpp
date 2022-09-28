#include "Computer.h"
#include "ComputerBlock.h"

ComputerBlock::ComputerBlock()
{
}

void ComputerBlock::CreateBlock()
{
	Computer* com = (Computer*)Block::getPlayer();
	Block::CreateBlock();

	if (b_gameOver == true)
	{
		return;
	}
	com->HightLineHoleBump();
}
