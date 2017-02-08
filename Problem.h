#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#define TILE_CNT 9 //The total number of spaces on the board
enum action {UP, DOWN, LEFT, RIGHT, NONE};

struct Node
{
	Node *parent;
	int *state;
	int path_cost;
	action prev_act;

	Node(int *s, int c = 0, action a = NONE, Node *p = NULL);

	~Node();
};

/*class Tree
{
		Node *root;
		Node *parent;
		Node *cur;
	
	public
		//Constructor
		Tree(int *state);

		//Destructor
		~Tree();

		void add_child(int *state, action prev_act, int h_cost = 0);
};*/

class Problem
{
		int *start_state;
		int *goal_state;

	public:
		//Constructor
		Problem(int *input);

		//Destructor
		~Problem();

		//Operators
		void move_blank_up();
		void move_blank_down();
		void move_blank_left();
		void move_blank_right();
};

#endif
