#include "Problem.h"
#include <iostream>

//Node functions
Node::Node(int *s, int c, int h, action a)
:path_cost(c), h_cost(h), prev_act(a)
{
	state = new int[TILE_CNT];
	memcpy(state, s, sizeof (int[TILE_CNT]));
}

Node::Node(const Node &og_node)
{
	path_cost = og_node.path_cost;
	h_cost = og_node.h_cost;
	prev_act = og_node.prev_act;
	state = new int[TILE_CNT];
	memcpy(state, og_node.state, sizeof (int[TILE_CNT]));
}

Node::~Node()
{
	delete[] state;
}

void Node::getState()
{
	for(int i = 0; i < TILE_CNT; i++)
	{
		if((i % PUZZLE_DIMENSION) == 0)
		{
			printf("\t");
		}
		if(state[i] == 0)
		{
			printf("b ");
		}
		else
		{
			printf("%d ", state[i]);
		}
		if(((i + 1) % PUZZLE_DIMENSION) == 0)
		{
			printf("\n");
		}
	}
}
//End of Node functions

//Tree functions
Tree::tNode::tNode(Node &n)
:parent(NULL), u_child(NULL), d_child(NULL), l_child(NULL), r_child(NULL)
{
	info = new Node(n);
}

Tree::tNode::~tNode()
{
	delete info;
	if(u_child != NULL)
	{
		delete u_child;
	}
	if(d_child != NULL)
	{
		delete d_child;
	}
	if(l_child != NULL)
	{
		delete l_child;
	}
	if(r_child != NULL)
	{
		delete r_child;
	}
	parent = NULL;
}

Tree::Tree()
{
	root = NULL;
	cur = root;
}

Tree::Tree(Node &start)
{
	root = new tNode(start);
	cur = root;
}

Tree::~Tree()
{
	cur = NULL;
	delete root;
}

void Tree::printPathR(tNode *c)
{
	if(c->parent == NULL)
	{
		printf("Start state:");
		c->info->getState();
	}
	else
	{
		printPathR(c->parent);
		switch(c->info->prev_act)
		{
			case LEFT:
				printf("Move the blank left...\n");
				break;
			case RIGHT:
				printf("Move the blank right...\n");
				break;
			case UP:
				printf("Move the blank up...\n");
				break;
			case DOWN:
				printf("Move the blank down...\n");
				break;
			default:
				printf("Don't know how you get here...\n");
				break;
		}
		c->info->getState();
	}
	printf("\n");
	return;
}

void Tree::printPath()
{
	printPathR(cur);
	return;
}

void Tree::addUp(Node &child)
{
}

void Tree::addDown(Node &child)
{
}

void Tree::addLeft(Node &child)
{
}

void Tree::addRight(Node &child)
{
}
//End of Tree functions

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
	new_state[blank_ind] = new_state[blank_ind - PUZZLE_DIMENSION];
	new_state[blank_ind - PUZZLE_DIMENSION] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, UP);
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
	new_state[blank_ind] = new_state[blank_ind + PUZZLE_DIMENSION];
	new_state[blank_ind + PUZZLE_DIMENSION] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, DOWN);
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
	new_state[blank_ind] = new_state[blank_ind - 1];
	new_state[blank_ind - 1] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, LEFT);
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
	new_state[blank_ind] = new_state[blank_ind + 1];
	new_state[blank_ind + 1] = 0;
	Node *child = new Node(new_state, cur.path_cost + 1, 0, RIGHT);
	delete[] new_state;
	return child;
}
