#include <iostream>
#include <string.h>
#include <math.h>
#include "Problem.h"

int puzzle[TILE_CNT] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
int puzzle_dimension = (int)sqrt((int)TILE_CNT);

bool isInteger(char *num)
{
	if(num[0] == '-')
	{
		if(num[1] == '\0')
		{
			return false;
		}
		for(int i = 1; num[i] != '\0'; i++)
		{
			if(!isdigit(num[i]))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for(int i = 0; num[i] != '\0'; i++)
		{
			if(!isdigit(num[i]))
			{
				return false;
			}
		}
		return true;
	}

}

void customPuzzleMaker()
{
	std::string input;
	printf("Enter your puzzle, use a zero to represent the blank\n");
	int i = 0;
	bool valid_num;
	while(i < puzzle_dimension)
	{
		printf("Enter %d numbers for row %d, use space or tabs between numbers:\t", puzzle_dimension, i+1);
		std::getline(std::cin, input);
		char *input_numbers = new char[input.length()+1];
		std::strcpy(input_numbers, input.c_str());
		char *number = std::strtok(input_numbers, " \t");
		//Check to see if enough numbers were entered and if the correct numbers were entered
		valid_num = true;
		int num_cnt = 0;
		while(number != 0)
		{
			//If not a number, error
			if(!isInteger(number))
			{
				valid_num = false;
				printf("ERROR: Number %s is not a number\n", number);
			}
			//If a negative number, error
			else if(number[0] == '-')
			{
				valid_num = false;
				printf("ERROR: Number %s is negative\n", number);
			}
			//If too big a number, error
			else if((int)strtol(number, NULL, 10) > TILE_CNT-1)
			{
				valid_num = false;
				printf("ERROR: Number %s is too big\n", number); 
			}
			number = std::strtok(NULL, " \t");
			num_cnt++;
		}
		if(!valid_num)
		{
			printf("       Valid inputs are whole numbers from 0 - %d\n", TILE_CNT-1);
			delete[] input_numbers;
			continue;
		}
		//Check for correct number of numbers
		if(num_cnt != puzzle_dimension)
		{
			printf("ERROR: %d number(s) were entered for row %d\n", num_cnt, i+1);
			delete[] input_numbers;
			continue;
		}
		//Errors: duplicate numbers in the array
		delete[] input_numbers;
		i++;
	}
}

int main(int argc, char **argv)
{
	printf("Welcome to %s's %d-puzzle solver.\n", "amacp001", TILE_CNT-1);
	printf("Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle\n");
	std::string choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(100, '\n');
	for(; choice != "1" && choice != "2"; std::cin >> choice)
	{
		printf("Invalid Response!\n");
		printf("Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle\n");
	}
	if(choice == "2")
	{
		customPuzzleMaker();
	}
	return 0;
}
