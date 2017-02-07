#include "Problem.h"
#include <iostream>

//Node functions
Node::Node(char *s, int c, action a, Node *p)
	:path_cost(c), prev_act(a), parent(p)
{
	state = new char[TILE_CNT+1];
	std::memcpy(state, s, sizeof state);
}

Node::~Node()
{
	delete state;
}

//Tree functions
Tree::Tree(char *state)
{
	root = new Node(state);
	parent = new Node(state);
	child = new Node(state);
}

Tree::~Tree()
{
	delete root;
	delete parent;
	delete child;
}

void Tree::add_child(char *state, action prev_act, int h_cost)
{
}

//Problem functions
Problem::Problem(int *input)
{
	start_state = new char[TILE_CNT+1];
	std::memcpy(start_state, input, sizeof start_state);
	goal_state = new int[TILE_CNT];
	for(unsigned int i = 0; i < TILE_CNT+1; i++)
	{
		if(i == TILE_CNT-1)
		{
			goal_state[i] = '\0';
		}
		else if(i == TILE_CNT-2)
		{
			goal_state[i] = 'b';
		}
		else
		{
			goal_state[i] = '1'+i;
		}
	}
}

Problem::~Problem()
{
	delete start_state;
	delete goal_state;
}

void Problem::move_blank_up()
{
}

void Problem::move_blank_down()
{
}

void Problem::move_blank_left()
{
}

void Problem::move_blank_right()
{
}
