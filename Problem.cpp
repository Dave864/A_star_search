#include "Problem.h"
#include <iostream>

//Node functions
Node::Node(int *s, int c, int h, action a, Node *p)
:parent(p), path_cost(c), h_cost(h), prev_act(a)
{
	state = new int[TILE_CNT];
	memcpy(state, s, sizeof (int[TILE_CNT]));
}

Node::Node(const Node &og_node)
{
	parent = og_node.parent;
	path_cost = og_node.path_cost;
	h_cost = og_node.h_cost;
	prev_act = og_node.prev_act;
	state = new int[TILE_CNT];
	memcpy(state, og_node.state, sizeof (int[TILE_CNT]));
}

Node::~Node()
{
	delete[] state;
	parent = NULL;
}

void Node::pstate()
{
	printf("{ ");
	for(unsigned i = 0; i < TILE_CNT; i++)
	{
		printf("%d ", state[i]);
	}
	printf("}\n");
}

/*bool Node::operator <(Node &rhs)
{
	return((this->path_cost + this->h_cost) < (rhs.path_cost + rhs.h_cost));
}

bool Node::operator >(Node &rhs)
{
	return((this->path_cost + this->h_cost) > (rhs.path_cost + rhs.h_cost));
}

bool Node::operator ==(Node &rhs)
{
	return((this->path_cost + this->h_cost) == (rhs.path_cost + rhs.h_cost));
}*/

/*
//Tree functions
Tree::Tree(int *state)
{
	root = new Node(state);
	cur = NULL;
}

Tree::~Tree()
{
	delete root;
	delete cur;
}

void Tree::add_child(char *state, action prev_act, int h_cost)
{
}*/


//Problem functions
Problem::Problem(int *input)
{
	start_state = new int[TILE_CNT];
	std::memcpy(start_state, input, sizeof (int[TILE_CNT]));
	goal_state = new int[TILE_CNT];
	for(unsigned int i = 0; i < TILE_CNT; i++)
	{
		goal_state[i] = i+1;
		if(i == TILE_CNT-1)
		{
			goal_state[i] = 0;
		}
	}
}

Problem::~Problem()
{
	delete[] start_state;
	delete[] goal_state;
}

int Problem::getBlankIndex(int *state)
{
	for(int index = 0; index < TILE_CNT; index++)
	{
		if(state[index] == 0)
		{
			return index;
		}
	}
	return -1;
}

int* Problem::getStart()
{
	return start_state;
}

int* Problem::getGoal()
{
	return goal_state;
}

Node* Problem::moveBlankUp(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if((blank_ind - PUZZLE_DIMENSION) < 0)
	{
		return NULL;
	}
	int *new_state = new int[TILE_CNT];
	std::memcpy(new_state, cur.state, sizeof (int[TILE_CNT]));
	Node *child = new Node(new_state, cur.path_cost + 1, 0, UP, &cur);
	delete[] new_state;
	return child;
}

Node* Problem::moveBlankDown(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if((blank_ind + PUZZLE_DIMENSION) >= TILE_CNT)
	{
		return NULL;
	}
	int *new_state = new int[TILE_CNT];
	std::memcpy(new_state, cur.state, sizeof (int[TILE_CNT]));
	Node *child = new Node(new_state, cur.path_cost + 1, 0, DOWN, &cur);
	delete[] new_state;
	return child;
}

Node* Problem::moveBlankLeft(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if((blank_ind % PUZZLE_DIMENSION) == 0)
	{
		return NULL;
	}
	int *new_state = new int[TILE_CNT];
	std::memcpy(new_state, cur.state, sizeof (int[TILE_CNT]));
	Node *child = new Node(new_state, cur.path_cost + 1, 0, LEFT, &cur);
	delete[] new_state;
	return child;
}

Node* Problem::moveBlankRight(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if(((blank_ind + 1) % PUZZLE_DIMENSION) == 0)
	{
		return NULL;
	}
	int *new_state = new int[TILE_CNT];
	std::memcpy(new_state, cur.state, sizeof(int[TILE_CNT]));
	Node *child = new Node(new_state, cur.path_cost + 1, 0, RIGHT, &cur);
	delete[] new_state;
	return child;
}
