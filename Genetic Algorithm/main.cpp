#include <iostream>

#include "CGameBoard.h"
#include "CGeneticAlgorithm.h"

int main()
{
	int sizeInput = 0;
	int boardSizeInput = 0;

	// Queens Problem using genetic algorithm
	std::cout << "Please input the size of the board: ";
	std::cin >> boardSizeInput;
	std::cout << "Please input the size of the population: ";
	std::cin >> sizeInput;
	
	CGeneticAlgorithm geneticAlgorithm(sizeInput, boardSizeInput);
}