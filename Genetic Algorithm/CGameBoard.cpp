#pragma once

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "CGameBoard.h"

struct Queens
{
	int x = 0;
	int y = 0;
};

CGameBoard::CGameBoard(int boardSize)
{
	// Creates a board filled with '-' (Board with no queens)
	std::vector<char>* temp;

	for (int i = 0; i < boardSize; i++)
	{
		temp = new std::vector<char>;
		for (int j = 0; j < boardSize; j++)
		{
			temp->push_back('-');
		}
		gameBoard.push_back(*temp);
		delete temp;
	}

	gameBoardSize = boardSize;
}

CGameBoard::~CGameBoard()
{

}

int CGameBoard::GetHeuristic()
{
	std::vector<Queens> boardsQueens;
	int attacks = 0;

	// Sets each queen to have an x and y to evaluate later
	for (int row = 0; row < gameBoardSize; row++)
	{
		for (int column = 0; column < gameBoardSize; column++)
		{
			if (gameBoard[row][column] == 'Q')
			{
				Queens queen;
				queen.x = row;
				queen.y = column;

				boardsQueens.push_back(queen);
			}
		}
	}

	// Gets the heuristic for queens horizontal and vertical
	for (int i = 0; i < (int)boardsQueens.size(); i++)
	{
		for (int j = 0; j < (int)boardsQueens.size(); j++)
		{
			if (i != j)
			{
				// Horizontal Check
				if (boardsQueens[i].x == boardsQueens[j].x)
				{
					attacks++;
				}
				// Vertical Check
				if (boardsQueens[i].y == boardsQueens[j].y)
				{
					attacks++;
				}
				// Diagonal Check
				if (abs(boardsQueens[i].x - boardsQueens[i].y) == abs(boardsQueens[j].x - boardsQueens[j].y))
				{
					attacks++;
				}
				if (abs(boardsQueens[i].x + boardsQueens[i].y) == abs(boardsQueens[j].x + boardsQueens[j].y))
				{
					attacks++;
				}
			}
		}
	}
	// returns the boards Heuristic
	return(attacks);
}

void CGameBoard::RandFilledBoard()
{
	// Randomly placing queens on each row
	for (int i = 0; i < gameBoardSize; i++)
	{
		int randCol = rand() % gameBoardSize;
		gameBoard[i][randCol] = 'Q';
	}
}

void CGameBoard::AlteredBoard(std::vector<std::vector<char>> currentBoard)
{
	int randRow = rand() % gameBoardSize;
	int randCol = rand() % gameBoardSize;

	// Clears the row to prevent added extra queen to the board
	for (int i = 0; i < gameBoardSize; i++)
	{
		for (int j = 0; j < gameBoardSize; j++)
		{
			if (i == randRow)
			{
				gameBoard[i][j] = '-';
			}
			else
			{
				gameBoard[i][j] = currentBoard[i][j];
			}
		}
	}

	// Randomly placing queen on a line
	gameBoard[randRow][randCol] = 'Q';
}

void CGameBoard::PrintBoard()
{
	// Prints the board to the console
	for (int i = 0; i < gameBoardSize; i++)
	{
		for (int j = 0; j < gameBoardSize; j++)
		{
			std::cout << gameBoard[i][j];
		}
		std::cout << std::endl;
	}
}