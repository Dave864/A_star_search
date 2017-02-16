#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include "Problem.h"

//Node comparison class for use in the frontier priority queue
class nodeComparison
{
	bool reverse;
	public:
		nodeComparison(bool revparam = false)
		{
			reverse = revparam;
		}
		bool operator() (Node *lhs, Node *rhs)
		{
			if(reverse)
			{
				return ((lhs->path_cost + lhs->h_cost) > (rhs->path_cost + rhs->h_cost));
			}
			else
			{
				return ((lhs->path_cost + lhs->h_cost) < (rhs->path_cost + rhs->h_cost));
			}
		}
};

int puzzle[TILE_CNT] = {};
int valid_numbers[TILE_CNT] = {};
std::vector<Node> explored;
std::vector<Node> frontier_contents;
std::priority_queue<Node*, std::vector<Node*>, nodeComparison> frontier;

//Checks if a char array is a positive or negative whole number
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

//GUI for making a custom puzzle
void customPuzzleMaker()
{
	std::string input;
	printf("Enter your puzzle, use a zero to represent the blank\n");
	bool valid_num;
	bool duplicate_num;
	int row;
	do
	{
		row = 0;
		while(row < PUZZLE_DIMENSION)
		{
			printf("Enter %d numbers for row %d, use space or tabs between numbers:\t", PUZZLE_DIMENSION, row+1);
			std::getline(std::cin, input);
			char *input_chars= new char[input.length()+1];
			std::strcpy(input_chars, input.c_str());
			char *number = std::strtok(input_chars, " \t");
			int *row_vals = new int[PUZZLE_DIMENSION];
			//Check to see if enough numbers were entered and if the correct numbers were entered
			valid_num = true;
			duplicate_num = false;
			int num_cnt = 0;
			for(;number != 0; num_cnt++, number = std::strtok(NULL, " \t"))
			{
				int num_val = 0;
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
				else if((num_val = (int)strtol(number, NULL, 10)) > TILE_CNT-1)
				{
					valid_num = false;
					printf("ERROR: Number %s is too big\n", number); 
				}
				//Add number to row_vals
				else
				{
					if(num_cnt < PUZZLE_DIMENSION)
					{
						row_vals[num_cnt] = num_val;
					}	
				}
			}
			if(!valid_num)
			{
				printf("       Valid inputs are whole numbers from 0 - %d\n", TILE_CNT-1);
				delete[] input_chars;
				delete[] row_vals;
				continue;
			}
			//Check for correct number of numbers
			if(num_cnt != PUZZLE_DIMENSION)
			{
				printf("ERROR: %d number(s) were entered for row %d\n", num_cnt, row+1);
				delete[] input_chars;
				delete[] row_vals;
				continue;
			}
			//add input to puzzle
			for(int col = 0; col < PUZZLE_DIMENSION; col++)
			{
				puzzle[(PUZZLE_DIMENSION*row)+col] = row_vals[col];
			}
			delete[] input_chars;
			delete[] row_vals;
			row++;
		}
		//Check for duplicate numbers
		printf("The puzzle you entered is\n");
		for(int i = 0; i < PUZZLE_DIMENSION; i++)
		{
			for(int j = 0; j < PUZZLE_DIMENSION; j++)
			{
				printf("%d ", puzzle[(PUZZLE_DIMENSION*i)+j]);
				if(valid_numbers[puzzle[(PUZZLE_DIMENSION*i)+j]] < 0)
				{
					duplicate_num = true;
				}
				else
				{
					valid_numbers[puzzle[(PUZZLE_DIMENSION*i)+j]] = -1;
				}
			}
			printf("\n");
		}
		if(duplicate_num)
		{
			printf("ERROR: You have entered duplicate numbers into your puzzle\n");
			printf("       Please enter a new puzzle with no duplicate numbers\n");
			//Reinitialize the valid_numbers
			for(int i = 0; i < TILE_CNT; i++)
			{
				valid_numbers[i] = i;
			}
		}
	}while(duplicate_num);
}

//Compares the contents of two int arrays and returns true if they are the same
bool sameState(const int *lhs, const int *rhs)
{
	for(int i = 0; i < TILE_CNT; i++)
	{
		if(lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

//Expands the leaf node into its child components
void expand(Problem &tile_problem, Node *leaf/*, heuristic*/)
{
	return;
}

//The main loop of the A_star search
void graphSearch(Problem tile_problem/*, heuristic*/)
{
	Node start(tile_problem.getStart());
	frontier.push(&start);
	frontier_contents.push_back(start);
	while(1)
	{
		if(frontier.empty())
		{
			//Failure
			return;
		}
		Node *leaf = frontier.top();
		frontier.pop();
		if(sameState(tile_problem.getGoal(), leaf->state))
		{
			//Success, return path from leaf to root
			return;
		}
		explored.push_back(*leaf);
		expand(tile_problem, leaf);
		return;
	}
	return;
}

int main(int argc, char **argv)
{
	//initialize default puzzle and valid_numbers
	for(int i = 0; i < TILE_CNT; i++)
	{
		puzzle[i] = TILE_CNT-i-1;
		valid_numbers[i] = i;
	}
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
	Problem my_problem(puzzle);
	graphSearch(my_problem);
	return 0;
}
