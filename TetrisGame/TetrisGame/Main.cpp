#include "GameRender.h"
#include "GameBoard.h"
#include "Block.h"
#include "Player.h"

int main()
{
	GameRender tetris;
	tetris.GameStart();
	while (tetris.b_runTetris)
	{
		tetris.BlockControl();
	}
	
	return 0;
}