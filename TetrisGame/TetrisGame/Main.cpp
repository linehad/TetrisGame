#include "GameRender.h"
#include "GameBoard.h"
#include "Block.h"
#include "Player.h"
#include "Computer.h"
#include "ComputerBlock.h"
#include "ComputerGameBoard.h"

int main()
{
	/*GameRender tetris;
	tetris.GameStart();
	while (tetris.b_runTetris)
	{
		tetris.BlockControl();
	}
	
	return 0;*/

	Computer com;
	ComputerGameBoard comGB;
	ComputerBlock comB;
	GameRender tetris(com, comGB, comB);
	tetris.GameStart();
	while (tetris.b_runTetris)
	{
		tetris.BlockControl();
	}

	return 0;
}