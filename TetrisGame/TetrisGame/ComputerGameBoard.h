#pragma once
#include "GameBoard.h"

class ComputerGameBoard : public GameBoard
{
private:

public:
	ComputerGameBoard();

	float AggregateHeight();
	float CompleteLines();
	float Holes();
	float Bumpiness();
};