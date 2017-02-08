#include <iostream>
#include "Problem.h"

int def_puzzle[TILE_CNT] = {8, 7, 6, 5, 4, 3, 2, 1, 0};

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
	if(choice == "1")
	{
	}
	else
	{
	}
	return 0;
}
