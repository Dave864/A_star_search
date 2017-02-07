#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#define TILE_CNT 8
enum action {UP, DOWN, LEFT, RIGHT, NONE};

struct Node
{
	Node *parent;
	int state[TILE_CNT];
	int path_cost;
	action last_act;
};

class Tree
{
		Node *root;
		Node *parent;
		Node *cur;
	
	public
		//Constructor
		Tree();

		//Destructor
		~Tree();
};

class Problem
{
		int start_state[TILE_CNT];
		int goal_state[TILE_CNT];

	public:
		//Constructor
		Problem(int input[]);

		//Destructor
		~Problem();

		//Operators
		void move_blank_up();
		void move_blank_down();
		void move_blank_left();
		void move_blank_right();
};

#endif
