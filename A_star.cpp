#include <iostream>
#include <math.h>
#include "Problem.h"

int puzzle[TILE_CNT] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
int puzzle_dimension = (int)sqrt((int)TILE_CNT);

void custom_puzzle_maker()
{
		printf("Enter your puzzle, use a zero to represent the blank\n");
		for(int i = 0; i < puzzle_dimension; i++)
		{
			printf("Enter row %d, use space or tabs between numbers:\t", i+1);
			//Errors: letters/special characters, negative numbers, too large numbers
			//Errors: duplicate numbers in the array
		}
}

int main(int argc, char **argv)
{
	printf("Welcome to %s's %d-puzzle solver.\n", "amacp001", TILE_CNT-1);
	printf("Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle\n");
	std::string choice;
	std::cin >> choice;
	for(; choice != "1" && choice != "2"; std::cin >> choice)
	{
		printf("Invalid Response!\n");
		printf("Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle\n");
	}
	if(choice == "2")
	{
		custom_puzzle_maker();
	}
	return 0;
}
