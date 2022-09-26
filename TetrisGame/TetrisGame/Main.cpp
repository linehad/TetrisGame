#include "GameRender.h"
#include "GameBoard.h"
#include "Block.h"
#include "Player.h"
#include "Computer.h"

int main()
{
	Computer com;
	GameRender tetris(com);
	tetris.GameStart();
	while (tetris.b_runTetris)
	{
		tetris.BlockControl();
	}
	
	return 0;
}