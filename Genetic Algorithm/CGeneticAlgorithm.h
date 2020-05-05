#pragma once

#include <vector>
#include <iostream>
#include <algorithm>	// for random_shuffle

#include "CGameBoard.h"

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(int sizeInput, int boardSizeInput);
	~CGeneticAlgorithm();

	void SampleHeuristic(std::vector<CGameBoard> samplePop, CGameBoard bestInSample);
	void RandomSample(std::vector<CGameBoard> samplePop);
	void ParentShareInfo();

	int sizePopulation;
	int boardSize;
	float percentPop;

	std::vector<CGameBoard> firstSample;
	std::vector<CGameBoard> secondSample;

	std::vector<CGameBoard> boardsInPop;

	CGameBoard bestFirstSample;
	CGameBoard bestSecondSample;
	CGameBoard childBoard;

private:

};

