#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <math.h>
#define TILE_CNT 9 //The total number of spaces on the board
#define PUZZLE_DIMENSION (int)(sqrt(TILE_CNT)) //The dimensions of the puzzle
enum action {UP, DOWN, LEFT, RIGHT, NONE};

struct Node
{
	int *state;
	int path_cost;
	int h_cost;
	action prev_act;

	Node(int *s, int c = 0, int h = 0, action a = NONE);
	Node(const Node &og_node);

	~Node();

	void getState();
};


class Tree
{
	struct tNode
	{
		Node *info;
		tNode *parent;
		tNode *u_child;
		tNode *d_child;
		tNode *l_child;
		tNode *r_child;

		tNode(Node &n);
		~tNode();
	};
	
	tNode *root;
	tNode *cur;
	int expand_cnt;

	void printPathR(tNode *c);

	public:
		Tree();
		Tree(Node &start);
		~Tree();

		void printPath();

		void addUp(Node &child);
		void addDown(Node &child);
		void addLeft(Node &child);
		void addRight(Node &child);
};

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
