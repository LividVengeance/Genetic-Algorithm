#include "CGeneticAlgorithm.h"


CGeneticAlgorithm::CGeneticAlgorithm(int sizeInput, int boardSizeInput)
{
	sizePopulation = sizeInput;
	boardSize = boardSizeInput;

	// Creates a population of random CGameBoards with queens
	for (int i = 0; i < sizePopulation; i++)
	{
		CGameBoard* newBoard = new CGameBoard(boardSize);
		newBoard->RandFilledBoard();
		boardsInPop.push_back(newBoard);
	}

	std::vector<CGameBoard*> firstSample;
	std::vector<CGameBoard*> secondSample;

	// Get first parent 
	CGameBoard* bestFirstSample = new CGameBoard(boardSize);
	bestFirstSample->FillQueens();						// To make sure I get the best in the sample
	bestBoard = bestFirstSample;						// So not empty when checking at end
	RandomSample(&firstSample);							// Get random sample from pop
	SampleHeuristic(firstSample, bestFirstSample);		// Get best in sample

	// Get second parent
	CGameBoard* bestSecondSample = new CGameBoard(boardSize);
	bestSecondSample->FillQueens();						// To make sure I get the best in the sample
	RandomSample(&secondSample);						// Get random sample from pop
	SampleHeuristic(secondSample, bestSecondSample);	// Get best in sample

	// Get children
	NewPopulation(bestFirstSample, bestSecondSample);	// Get Child from parent
}

void CGeneticAlgorithm::NewSamples()
{
	iderations++;
	if (iderations >= sizePopulation)
	{
		GetBest();
		std::cout << bestBoard->GetHeuristic() << " - Final Solution" << std::endl;
	}
	else
	{
		std::vector<CGameBoard*> firstSample;
		std::vector<CGameBoard*> secondSample;

		// Get first parent 
		CGameBoard* bestFirstSample = new CGameBoard(boardSize);
		//bestFirstSample->FillQueens(); // To make sure I get the best in the sample

		bestFirstSample->RandFilledBoard();

		RandomSample(&firstSample);
		SampleHeuristic(firstSample, bestFirstSample);
		// Get second parent
		CGameBoard* bestSecondSample = new CGameBoard(boardSize);
		//bestSecondSample->FillQueens(); // To make sure I get the best in the sample

		bestSecondSample->RandFilledBoard();

		RandomSample(&secondSample);
		SampleHeuristic(secondSample, bestSecondSample);

		// Get children
		NewPopulation(bestFirstSample, bestSecondSample);
	}
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

void CGeneticAlgorithm::SampleHeuristic(std::vector<CGameBoard*> samplePop, CGameBoard* bestInSample)
{
	// Checks the sample boards for the best board - Getting the parent
	for (int i = 0; i < samplePop.size(); i++)
	{
		if (samplePop[i]->GetHeuristic() > bestInSample->GetHeuristic())
		{
			bestInSample = samplePop[i];
		}
	}
}

void CGeneticAlgorithm::RandomSample(std::vector<CGameBoard*>* samplePop)
{
	// Suffles the elements in population - Gets random % of population
	std::random_shuffle(boardsInPop.begin(), boardsInPop.end());
	for (int i = 0; i < boardsInPop.size() / 4; i++)
	{
		samplePop->push_back(boardsInPop[i]);
	}
}

void CGeneticAlgorithm::NewPopulation(CGameBoard* bestFirstSample, CGameBoard* bestSecondSample)
{
	// Generates a new population from parents
	boardsInPop.clear(); // Clears old pop
	while (boardsInPop.size() < sizePopulation)
	{
		CGameBoard* newChild = new CGameBoard(boardSize);
		ParentShareInfo(bestFirstSample, bestSecondSample, newChild);
		boardsInPop.push_back(newChild);
	}
	// Rerun will new pop
	NewSamples();
}

void CGeneticAlgorithm::ParentShareInfo(CGameBoard* bestFirstSample, CGameBoard* bestSecondSample, CGameBoard* newChild)
{
	int gene = rand() % bestFirstSample->gameBoardSize;

	for (int i = 0; i < bestFirstSample->gameBoardSize; i++)
	{
		for (int j = 0; j < bestFirstSample->gameBoardSize; j ++)
		{
			if (i <= gene)
			{
				newChild->gameBoard[i][j] = bestFirstSample->gameBoard[i][j];
			}
			else
			{
				newChild->gameBoard[i][j] = bestFirstSample->gameBoard[i][j];
			}
		}
	}

	MutationCheck(newChild);
}

void CGeneticAlgorithm::MutationCheck(CGameBoard* childBoard)
{
	int mutationChance = rand() % 25;
	if (mutationChance == 7)
	{
		int randRow = rand() % childBoard->gameBoardSize;
		int randCol = rand() % childBoard->gameBoardSize;

		// Clears the row to prevent added extra queen to the board
		for (int i = 0; i < childBoard->gameBoardSize; i++)
		{
			for (int j = 0; j < childBoard->gameBoardSize; j++)
			{
				if (i == randRow)
				{
					childBoard->gameBoard[i][j] = '-';
				}
			}
		}
		// Randomly placing queen on a line
		childBoard->gameBoard[randRow][randCol] = 'Q';
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

void CGeneticAlgorithm::GetBest()
{
	for (int i = 0; i < boardsInPop.size(); i++)
	{
		if (boardsInPop[i]->GetHeuristic() < bestBoard->GetHeuristic())
		{
			bestBoard = boardsInPop[i];
		}
	}
}