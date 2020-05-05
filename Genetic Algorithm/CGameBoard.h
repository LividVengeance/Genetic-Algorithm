#pragma once

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <vector>

class CGameBoard
{
public:
	CGameBoard(int boardSize);
	~CGameBoard();

	void FirstBoard();
	void AlteredBoard(std::vector<std::vector<char>> currentBoard);
	int GetHeuristic();
	void PrintBoard();

	std::vector<std::vector<char>> gameBoard;
private:

	int gameBoardSize;
};