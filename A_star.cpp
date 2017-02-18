#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string.h>
#include "Problem.h"

//Node comparison class for use in the frontier priority queue
class nodeComparison
{
	public:
		bool operator() (Node *lhs, Node *rhs)
		{
			return ((lhs->path_cost + lhs->h_cost) > (rhs->path_cost + rhs->h_cost));
		}
};

typedef int (*hfunc)(int *);
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
		//printf("The puzzle you entered is\n");
		for(int i = 0; i < PUZZLE_DIMENSION; i++)
		{
			for(int j = 0; j < PUZZLE_DIMENSION; j++)
			{
				//printf("%d ", puzzle[(PUZZLE_DIMENSION*i)+j]);
				if(valid_numbers[puzzle[(PUZZLE_DIMENSION*i)+j]] < 0)
				{
					duplicate_num = true;
				}
				else
				{
					valid_numbers[puzzle[(PUZZLE_DIMENSION*i)+j]] = -1;
				}
			}
			//printf("\n");
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

//Returns 0 for Uniform Cost Search
int ucs(int *state)
{
	return 0;
}

//Calculates the Misplaced Tile hueristic for a state
int misTileH(int *state)
{
	int h_val = 0;
	for(int i = 0; i < TILE_CNT; i++)
	{
		if(state[i] != 0 && (state[i] - 1) != i)
		{
			h_val++;
		}
	}
	return h_val;
}

//Calculates the Manhattan Distance hueristic for a state
int manDistH(int *state)
{
	int h_val = 0;
	int ind_x, ind_y;
	int num_x, num_y;
	for(int i = 0; i < TILE_CNT; i++)
	{
		if(state[i] != 0 && (state[i] - 1) != i)
		{
			num_y = (state[i] - 1)/PUZZLE_DIMENSION;
			num_x = (state[i] - 1) - (PUZZLE_DIMENSION * num_y);
			ind_y = i/PUZZLE_DIMENSION;
			ind_x = i - (PUZZLE_DIMENSION * ind_y);
			h_val += std::abs(num_y - ind_y) + std::abs(num_x - ind_x);
		}
	}
	return h_val;
	//return 0;
}

//Determine which heuristic to use
hfunc heuristicChoice()
{
	printf("\nEnter your choice of algorithm\n\t1. Uniform Cost Search\n\t2. A* with the Misplaced Tile heuristic\n\t3. A* with the Manhattan distance heuristic\n");
	printf("Enter a number 1, 2, or 3: ");
	std::string input;
	std::cin >> input;
	for(; input != "1" && input != "2" && input != "3"; std::cin >> input)
	{
		printf("Invalid input entered!\n");
		printf("Enter a number 1, 2, or 3: ");
	}
	printf("\n");
	if(input == "1")
	{
		return ucs;
	}
	else if(input == "2")
	{
		return misTileH;
	}
	else
	{
		return manDistH;
	}
}

//Display to std output what the current step of the algorithm is
void printStep(Node *node, bool first_node)
{
	if(first_node)
	{
		printf("Expanding state\n");
		node->getState();
	}
	else
	{
		printf("The best state to expand with a g(n) = %d and h(n) = %d is...\n", node->path_cost, node->h_cost);
		node->getState();
		printf("\tExpanding this node\n");
	}
	printf("\n");
}

//Compares the contents of two int arrays and returns true if they are the same
bool sameState(const int *lhs, const int *rhs)
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

//Checks to see if cur_state is in explored
bool inExplored(int *cur_state)
{
	for(unsigned int i = 0; i < explored.size(); i++)
	{
		if(sameState(cur_state, explored[i].state))
		{
			return true;
		}
	}
	return false;
}

//Checks to see if cur_state is in frontier
bool inFrontier(int *cur_state)
{
	for(unsigned int i = 0; i < explored.size(); i++)
	{
		if(sameState(cur_state, frontier_contents[i].state))
		{
			return true;
		}
	}
	return false;
}

//Expands the leaf node into its child components
void expand(Problem &tile_problem, Node leaf, hfunc myH)
{
	//Create up child
	Node *up_child = tile_problem.moveBlankUp(leaf);
	if(up_child != NULL)
	{
		if(!inExplored(up_child->state) && !inFrontier(up_child->state))
		{
			//apply heuristic
			up_child->h_cost = myH(up_child->state);
			frontier.push(up_child);
			frontier_contents.push_back(*up_child);
		}
	}
	//Create down child
	Node *down_child = tile_problem.moveBlankDown(leaf);
	if(down_child != NULL)
	{
		if(!inExplored(down_child->state) && !inFrontier(down_child->state))
		{
			//apply heuristic
			down_child->h_cost = myH(down_child->state);
			frontier.push(down_child);
			frontier_contents.push_back(*down_child);
		}
	}
	//Create left child
	Node *left_child = tile_problem.moveBlankLeft(leaf);
	if(left_child != NULL)
	{
		if(!inExplored(left_child->state) && !inFrontier(left_child->state))
		{
			//apply heuristic
			left_child->h_cost = myH(left_child->state);
			frontier.push(left_child);
			frontier_contents.push_back(*left_child);
		}
	}
	//Create right child
	Node *right_child = tile_problem.moveBlankRight(leaf);
	if(right_child != NULL)
	{
		if(!inExplored(right_child->state) && !inFrontier(right_child->state))
		{
			//apply heuristic
			right_child->h_cost = myH(right_child->state);
			frontier.push(right_child);
			frontier_contents.push_back(*right_child);
		}
	}
	return;
}

//The main loop of the A_star search
void graphSearch(Problem &tile_problem, hfunc myH)
{
	int expanded_cnt = 0;
	int max_queue_size = 0;
	Node start(tile_problem.getStart());
	frontier.push(&start);
	frontier_contents.push_back(start);
	bool first_node = true;
	while(1)
	{
		max_queue_size = (frontier.size() > (unsigned int)max_queue_size)? frontier.size() : max_queue_size;
		if(frontier.empty())
		{
			//Failure
			printf("Failed to find a solution...\n\n");
			printf("The search algorithm expanded a total of %d nodes\n", expanded_cnt);
			printf("The maximum number of nodes in the queue at any one time was %d\n", max_queue_size);
			return;
		}
		Node leaf = *frontier.top();
		frontier.pop();
		if(sameState(tile_problem.getGoal(), leaf.state))
		{
			//Success
			printf("Goal!!\n\n");
			printf("To solve this problem the search algorithm expanded a total of %d nodes\n", expanded_cnt);
			printf("The maximum number of nodes in the queue at any one time was %d\n", max_queue_size);
			printf("The depth of the goal node was %d\n", leaf.path_cost);
			return;
		}
		printStep(&leaf, first_node);
		explored.push_back(leaf);
		expanded_cnt++;
		expand(tile_problem, leaf, myH);
		first_node = false;
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
	graphSearch(my_problem, heuristicChoice());
	return 0;
}
