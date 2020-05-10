#include "CGeneticAlgorithm.h"


CGeneticAlgorithm::CGeneticAlgorithm(int sizeInput, int boardSizeInput)
{
	sizePopulation = sizeInput;
	boardSize = boardSizeInput;
	percentPop = 1;

	// Creates a population of random CGameBoards with queens
	for (int i = 0; i < sizePopulation; i++)
	{
		CGameBoard newBoard(boardSize);
		newBoard.RandFilledBoard();
		boardsInPop.push_back(newBoard);
	}

	// Get first parent 
	CGameBoard bestFirstSample(boardSize);
	RandomSample(firstSample);
	SampleHeuristic(firstSample, bestFirstSample);
	// Get second parent
	CGameBoard bestSecondSample(boardSize);
	RandomSample(secondSample);
	SampleHeuristic(secondSample, bestSecondSample);

	// Get children
	NewPopulation(bestFirstSample, bestSecondSample);
}

CGeneticAlgorithm::CGeneticAlgorithm()
{
	// Get first parent 
	CGameBoard bestFirstSample(boardSize);
	RandomSample(firstSample);
	SampleHeuristic(firstSample, bestFirstSample);
	// Get second parent
	CGameBoard bestSecondSample(boardSize);
	RandomSample(secondSample);
	SampleHeuristic(secondSample, bestSecondSample);

	// Get children
	NewPopulation(bestFirstSample, bestSecondSample);
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

void CGeneticAlgorithm::SampleHeuristic(std::vector<CGameBoard> samplePop, CGameBoard bestInSample)
{
	// Checks the sample boards for the best board
	for (int i = 0; i < samplePop.size(); i++)
	{
		if (samplePop[i].GetHeuristic() > bestInSample.GetHeuristic())
		{
			bestInSample = samplePop[i];
		}
	}
}

void CGeneticAlgorithm::RandomSample(std::vector<CGameBoard> samplePop)
{
	// Gets random % of population

	// Suffles the elements in population
	std::random_shuffle(boardsInPop.begin(), boardsInPop.end());
	for (int i = 0; i < boardsInPop.size() / percentPop; i++)
	{
		samplePop.push_back(boardsInPop[i]);
	}
}

void CGeneticAlgorithm::NewPopulation(CGameBoard firstSample, CGameBoard secondSample)
{
	boardsInPop.clear();
	while (boardsInPop.size() < sizePopulation)
	{
		CGameBoard newChild(boardSize);
		ParentShareInfo(firstSample, secondSample, newChild);
	}
}

void CGeneticAlgorithm::ParentShareInfo(CGameBoard firstSample, CGameBoard secondSample, CGameBoard newChild)
{
	int gen = rand() % firstSample.gameBoardSize;

	for (int i = 0; i < firstSample.gameBoardSize; i++)
	{
		for (int j = 0; j < firstSample.gameBoardSize; j ++)
		{
			if (i <= gen)
			{
				newChild.gameBoard[i][j] = firstSample.gameBoard[i][j];
			}
			else
			{
				newChild.gameBoard[i][j] = secondSample.gameBoard[i][j];
			}
		}
	}

	MutationCheck(newChild);
	iderations++;
	if (iderations < boardSize)
	{
		std::cout << newChild.GetHeuristic() << std::endl;
		CGeneticAlgorithm();
	}
	std::cout << newChild.GetHeuristic() << "Final Solution" << std::endl;
}

void CGeneticAlgorithm::MutationCheck(CGameBoard childBoard)
{
	int chance = rand() % 100;
	if (chance == 0)
	{
		int randRow = rand() % childBoard.gameBoardSize;
		int randCol = rand() % childBoard.gameBoardSize;

		// Clears the row to prevent added extra queen to the board
		for (int i = 0; i < childBoard.gameBoardSize; i++)
		{
			for (int j = 0; j < childBoard.gameBoardSize; j++)
			{
				if (i == randRow)
				{
					childBoard.gameBoard[i][j] = '-';
				}
			}
		}
		// Randomly placing queen on a line
		childBoard.gameBoard[randRow][randCol] = 'Q';
	}
}

void CGeneticAlgorithm::ClearBoard(CGameBoard childBoard)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			childBoard.gameBoard[i][j] = '-';
		}
	}
}

void CGeneticAlgorithm::ClearPop(CGameBoard firstSample, CGameBoard secondSample)
{
	//for (int i = 0; i < boardsInPop.size(); i++)
	//{
	//	if (!(boardsInPop[i].gameBoard == firstSample.gameBoard) || !(boardsInPop[i].gameBoard == secondSample.gameBoard))
	//	{
	//		delete boardsInPop[i];
	//
	//	}
	//}
	boardsInPop.clear();
}