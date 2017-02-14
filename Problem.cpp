#include "Problem.h"
#include <iostream>

//Node functions
Node::Node(int *s, int c, int h, action a, Node *p)
:parent(p), path_cost(c), h_cost(h), prev_act(a)
{
	state = new int[TILE_CNT];
	memcpy(state, s, sizeof state);
}

Node::~Node()
{
	delete[] state;
	parent = NULL;
}

bool Node::operator <(Node &rhs)
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
}

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
	std::memcpy(start_state, input, sizeof start_state);
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

int* Problem::getStart()
{
	return start_state;
}

int* Problem::getGoal()
{
	return goal_state;
}

Node* Problem::moveBlankUp(Node *cur)
{
	return NULL;
}

Node* Problem::moveBlankDown(Node *cur)
{
	return NULL;
}

Node* Problem::moveBlankLeft(Node *cur)
{
	return NULL;
}

Node* Problem::moveBlankRight(Node *cur)
{
	return NULL;
}
