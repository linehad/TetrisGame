#include "ComputerGameBoard.h"

ComputerGameBoard::ComputerGameBoard()
{

}

float ComputerGameBoard::AggregateHeight()
{
    std::vector<int> height;
    height.resize(10, 0);

    for (int i = 2; i < 12; i++)
    {
        for (int j = 2; j < 22; j++)
        {
            if (board[j][i] == 2)
            {
                height[i - 2] = 22 - j;
                break;
            }
        }
    }
    int heightSum = 0;
    for (int i = 0; i < height.size(); i++)
    {
        heightSum += height[i];
    }
    
    return heightSum;
}

float ComputerGameBoard::CompleteLines()
{
    int linesCount = 0;
    for (int i = 2; i < 22; i++)
    {
        int lineClearCount = 0;
        for (int j = 2; j < 12; j++)
        {
            if (board[i][j] == 2)
            {
                lineClearCount += 2;
                if (lineClearCount == 20)
                {
                    linesCount++;
                }
            }
        }
    }

    return linesCount;
}

float ComputerGameBoard::Holes()
{
    std::vector<int> height;
    height.resize(10, 0);

    for (int i = 2; i < 12; i++)
    {
        for (int j = 2; j < 22; j++)
        {
            if (board[j][i] == 2)
            {
                height[i - 2] = 22 - j;
                break;
            }
        }
    }

    int holeSum = 0;
    for (int i = 2; i < 12; i++)
    {
        for (int j = 22 - height[i - 2]; j < 22; j++)
        {
            if (board[j][i] != 2)
            {
                holeSum++;
            }
        }
    }

    return holeSum;
}

float ComputerGameBoard::Bumpiness()
{
    std::vector<int> height;
    height.resize(10, 0);

    for (int i = 2; i < 12; i++)
    {
        for (int j = 2; j < 22; j++)
        {
            if (board[j][i] == 2)
            {
                height[i - 2] = 22 - j;
                break;
            }
        }
    }

    int bumpSum = 0;
    for (int i = 0; i < height.size() - 1; i++)
    {
        bumpSum += abs(height[i] - height[i + 1]);
    }

    return bumpSum;
}


