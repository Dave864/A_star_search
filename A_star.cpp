#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string.h>
#include "Problem.h"

//Node comparison class for use in the frontier priority queue
class nodeComparison
{
	public:
		bool operator() (Node *lhs, Node *rhs)
		{
			return ((lhs->path_cost + lhs->h_cost) < (rhs->path_cost + rhs->h_cost));
		}
};

std::vector<int> puzzle (TILE_CNT, 0);
std::vector<int> valid_numbers (TILE_CNT, 0);
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
bool sameState(const std::vector<int> lhs, const std::vector<int> rhs)
{
	for(unsigned int i = 0; i < TILE_CNT; i++)
	{
		if(lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

//Checks to see if the state of the node is in the frontier
bool inFrontier(Node node)
{
	for(unsigned int i = 0; i < frontier_contents.size(); i++)
	{
		if(sameState(node.state, frontier_contents[i].state))
		{
			return true;
		}
	}
	return false;
}

//Checks to see if the state of the node in in the explored set
bool inExplored(Node node)
{
	for(unsigned int i = 0; i < explored.size(); i++)
	{
		if(sameState(node.state, explored[i].state))
		{
			return true;
		}
	}
	return false;
}

//Removes node from frontier_contents
void removeFrontierContent(Node node)
{
	for(unsigned int i = 0; i < frontier_contents.size(); i++)
	{
		if(sameState(node.state, frontier_contents[i].state))
		{
			frontier_contents.erase(frontier_contents.begin()+i);
			return;
		}
	}
	return;
}

//Expands the leaf node into its child components
void expand(Problem &tile_problem, Node leaf/*, heuristic*/)
{
	//Expand by moving the blank left
	Node *left_child = tile_problem.moveBlankLeft(leaf);
	if(left_child != NULL)
	{
		if(!inExplored(*left_child) && !inFrontier(*left_child))
		{
			//apply heuristic
			frontier.push(left_child);
			frontier_contents.push_back(*left_child);
		}
	}
	//Expand by moving the blank right
	Node *right_child = tile_problem.moveBlankRight(leaf);
	if(right_child != NULL)
	{
		//apply heuristic
		if(!inExplored(*right_child) && !inFrontier(*right_child))
		{
			frontier.push(right_child);
			frontier_contents.push_back(*right_child);
		}
	}
	//Expand by moving the blank up
	Node *up_child = tile_problem.moveBlankUp(leaf);
	if(up_child != NULL)
	{
		if(!inExplored(*up_child) && !inFrontier(*up_child))
		{
			//apply heuristic
			frontier.push(up_child);
			frontier_contents.push_back(*up_child);
		}
	}
	//Expand by moving the blank down
	Node *down_child = tile_problem.moveBlankDown(leaf);
	if(down_child != NULL)
	{
		if(!inExplored(*down_child) && !inFrontier(*down_child))
		{
			//apply heuristic
			frontier.push(down_child);
			frontier_contents.push_back(*down_child);
		}
	}
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
			printf("Failed to solve the puzzle.\n");
			return;
		}
		Node leaf = *(frontier.top());
		frontier.pop();
		removeFrontierContent(leaf);
		if(sameState(tile_problem.getGoal(), leaf.state))
		{
			//Success, return path from leaf to root
			printf("Successfully solved the puzzle!\n");
			return;
		}
		explored.push_back(leaf);
		expand(tile_problem, leaf);
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
