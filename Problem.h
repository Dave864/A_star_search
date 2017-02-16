#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <math.h>
#define TILE_CNT 9 //The total number of spaces on the board
#define PUZZLE_DIMENSION (int)(sqrt(TILE_CNT)) //The dimensions of the puzzle
enum action {UP, DOWN, LEFT, RIGHT, NONE};

struct Node
{
	Node *parent;
	int *state;
	int path_cost;
	int h_cost;
	action prev_act;

	Node(int *s, int c = 0, int h = 0, action a = NONE, Node *p = NULL);
	Node(const Node &og_node);

	~Node();

	void pstate();

	/*bool operator <(Node &rhs);
	bool operator >(Node &rhs);
	bool operator ==(Node &rhs);*/
};

/*
class Tree
{
		Node *root;
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

		int getBlankIndex(int *state);

	public:
		//Constructor
		Problem(int *input);

		//Destructor
		~Problem();

		int* getStart();
		int* getGoal();

		//Operators
		Node* moveBlankUp(Node &cur);
		Node* moveBlankDown(Node &cur);
		Node* moveBlankLeft(Node &cur);
		Node* moveBlankRight(Node &cur);
};

#endif
