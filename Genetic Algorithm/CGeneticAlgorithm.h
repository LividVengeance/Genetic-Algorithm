#pragma once

#include <vector>
#include <iostream>
#include <algorithm>	// for random_shuffle

#include "CGameBoard.h"

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(int sizeInput, int boardSizeInput);
	CGeneticAlgorithm();
	~CGeneticAlgorithm();

	void SampleHeuristic(std::vector<CGameBoard> samplePop, CGameBoard bestInSample);
	void RandomSample(std::vector<CGameBoard> samplePop);
	void ParentShareInfo(CGameBoard firstSample, CGameBoard secondSample, CGameBoard newChild);
	void NewPopulation(CGameBoard firstSample, CGameBoard secondSample);
	void MutationCheck(CGameBoard childBoard);
	void ClearBoard(CGameBoard childBoard);
	void ClearPop(CGameBoard firstSample, CGameBoard secondSample);

	int sizePopulation;
	int boardSize;
	int percentPop;
	int iderations = 0;

	std::vector<CGameBoard> firstSample;
	std::vector<CGameBoard> secondSample;

	std::vector<CGameBoard> boardsInPop;

	CGameBoard* bestBoard;

private:

};

