#include "CGeneticAlgorithm.h"


CGeneticAlgorithm::CGeneticAlgorithm(int sizeInput, int boardSizeInput)
{
	sizePopulation = sizeInput;
	boardSize = boardSizeInput;
	percentPop = 0.1f;

	// Creates a population of random CGameBoards with queens
	for (int i = 0; i < sizePopulation; i++)
	{
		CGameBoard newBoard(boardSize);
		newBoard.RandFilledBoard();
		boardsInPop.push_back(newBoard);
	}

	// Get first parent 
	RandomSample(firstSample);
	SampleHeuristic(firstSample, bestFirstSample);
	// Get second parent 
	RandomSample(secondSample);
	SampleHeuristic(secondSample, bestSecondSample);
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

void CGeneticAlgorithm::ParentShareInfo()
{

}