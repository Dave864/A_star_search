#include "Problem.h"
#include <iostream>
#include <vector>

//Node functions
Node::Node(std::vector<int> s, int c, int h, action a, Node *p)
:parent(p), state(s), path_cost(c), h_cost(h), prev_act(a){}

Node::Node(const Node &og_node)
{
	parent = og_node.parent;
	path_cost = og_node.path_cost;
	h_cost = og_node.h_cost;
	prev_act = og_node.prev_act;
	state = og_node.state;
}

Node::~Node()
{
	parent = NULL;
}

void Node::printState()
{
	printf("{ ");
	for(int i = 0; i < TILE_CNT; i++)
	{
		printf("%d ",state[i]);
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
Problem::Problem(std::vector<int> input)
{
	start_state = input;
	for(unsigned int i = 0; i < TILE_CNT; i++)
	{
		goal_state.push_back(i+1);
		if(i == TILE_CNT-1)
		{
			goal_state[i] = 0;
		}
	}
}

Problem::~Problem()
{
}

int Problem::getBlankIndex(std::vector<int> state)
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

std::vector<int> Problem::getStart()
{
	return start_state;
}

std::vector<int> Problem::getGoal()
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
	std::vector<int> new_state = cur.state;
	new_state[blank_ind] = new_state[blank_ind - PUZZLE_DIMENSION];
	new_state[blank_ind - PUZZLE_DIMENSION] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, UP, &cur);
	return child;
}

Node* Problem::moveBlankDown(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if((blank_ind + PUZZLE_DIMENSION) >= TILE_CNT)
	{
		return NULL;
	}
	std::vector<int> new_state = cur.state;
	new_state[blank_ind] = new_state[blank_ind + PUZZLE_DIMENSION];
	new_state[blank_ind + PUZZLE_DIMENSION] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, DOWN, &cur);
	return child;
}

Node* Problem::moveBlankLeft(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if((blank_ind % PUZZLE_DIMENSION) == 0)
	{
		return NULL;
	}
	std::vector<int> new_state = cur.state;
	new_state[blank_ind] = new_state[blank_ind - 1];
	new_state[blank_ind - 1] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, LEFT, &cur);
	return child;
}

Node* Problem::moveBlankRight(Node &cur)
{
	int blank_ind = getBlankIndex(cur.state);
	if(((blank_ind + 1) % PUZZLE_DIMENSION) == 0)
	{
		return NULL;
	}
	std::vector<int> new_state = cur.state;
	new_state[blank_ind] = new_state[blank_ind - 1];
	new_state[blank_ind - 1] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, RIGHT, &cur);
	return child;
}
