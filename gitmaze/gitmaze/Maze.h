#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Node.h"

class Maze
{
public:
	Node * getBase();

	void printMaze();

	Maze(int mazeRowWidth);

private:
	Node * base;

	std::vector<Node *> mazeVect;

	int rowWidth;
	int numNodes;

	void createMaze(int newRowWidth);
	void setPerimeter();
	void fillDoors();
	void randomizeDoors();
	void prims();
	void recursivePrims(Node * n, Node * p, std::vector<Node *> & v);

	bool joinNodes(Node * n1, Node * n2);

	Node * findRandomNeighbor(bool unvisited);

};

Maze::Maze(int mazeRowWidth)
{
	rowWidth = std::max(1, mazeRowWidth);
	createMaze(rowWidth);
	//setPerimeter();
	//randomizeDoors();
	prims();
}

Node * Maze::getBase()
{
	return base;
}

void Maze::createMaze(int newRowWidth)
{
	// Keep track of how wide our current row is
	int currentRowWidth = 1;

	// Calc total num nodes needed
	numNodes = newRowWidth * newRowWidth;

	// Create the base node
	base = new Node(0, 0, 0, 0);
	mazeVect.push_back(base);

	// Keep track of the node we are at right now
	Node * current = base;

	for (int i = 0; i < numNodes - 1; i++)
	{
		Node * newNode = new Node(0, 0, 0, 0);
		newNode->index = i + 1;
		mazeVect.push_back(newNode);

		// If we are loading nodes onto the current row
		if (currentRowWidth < rowWidth)
		{
			current->setRight(newNode);
			newNode->setLeft(current);
			if (current->getUp() != nullptr && current->getUp()->getRight() != nullptr)
			{
				newNode->setUp(current->getUp()->getRight());
				current->getUp()->getRight()->setDown(newNode);
			}
			currentRowWidth++;
		}
		// Else, we need to start a new row
		else
		{
			currentRowWidth = 1;

			// Navigate back to base
			current = base;

			// Step down the left-hand-side of maze until we get to lowest row
			while (current->getDown() != nullptr)
			{
				current = current->getDown();
			}

			// Start a new row below the current lowest
			current->setDown(newNode);
			newNode->setUp(current);
		}

		current = newNode;
	}
}

// Sets all the doors on the edge of the maze to be closed
void Maze::setPerimeter()
{
	Node * current = base;
	Node * leftmost = base;

	while (leftmost != nullptr)
	{
		while (current != nullptr)
		{
			for (int i = 0; i < 4; i++)
			{
				if (current->link[i] == nullptr)
					current->door[i] = 1;
			}

			current = current->getRight();
		}
		leftmost = leftmost->getDown();
		current = leftmost;
	}
}

// Sets ALL doors in the maze to be closed.
void Maze::fillDoors()
{
	Node * current = base;
	Node * leftmost = base;

	while (leftmost != nullptr)
	{
		while (current != nullptr)
		{
			for (int i = 0; i < 4; i++)
			{
				current->door[i] = 1;
			}

			current = current->getRight();
		}
		leftmost = leftmost->getDown();
		current = leftmost;
	}
}

// Prims' algorithm
void Maze::prims()
{
	if (base == nullptr)
		return;

	fillDoors();

	std::vector<Node *> v = { base };
	//recursivePrims(base, base, vect);

	while (!v.empty())
	{
		// Get random number from size of vector
		srand(time(NULL));
		int randint = rand() % v.size();

		// Pop current randomly selected from vector
		Node * c = v[randint];
		v.erase(v.begin() + randint);

		// Mark c visited
		c->visited = true;

		// Move linked neighbors to vector so we can shuffle
		std::vector<Node *> vlink;
		vlink.clear();
		for (int i = 0; i < 4; i++)
		{
			vlink.push_back(c->link[i]);
		}
		std::random_shuffle(vlink.begin(), vlink.end());

		// Join c and randomly selected visited neighbor
		for (int i = 3; i >= 0; i--)
		{
			if (vlink.at(i) != nullptr && vlink.at(i)->visited == true)
			{
				joinNodes(c, vlink[i]);
				break;
			}
		}

		// Get c's frontiers and push them to vector
		for (int i = 0; i < 4; i++)
		{
			// If c's frontiers have not been visited and are not already in the vector
			if (c->link[i] != nullptr && c->link[i]->visited == false && c->link[i]->inlist == false)
			{
				v.push_back(c->link[i]);
				c->link[i]->inlist = true;
			}
		}

		printMaze();
		//system("pause");
		system("cls");
	}
}

// Recursive part of Prims' algorithm
void Maze::recursivePrims(Node * n, Node * p, std::vector<Node *> & v)
{
	//if (n->visited)
	//	return;

	// VISIT
	n->visited = true;

	// Add frontier nodes to vector (EXPAND)
	for (int i = 0; i < 4; i++)
	{
		if (n->link[i] != nullptr && n->link[i]->visited == false && n->link[i]->inlist == false)
		{
			v.push_back(n->link[i]);
			n->link[i]->inlist = true;
		}
	}
	
	printMaze();
	std::cout << "Vector Size: " << v.size() << std::endl;
	//system("pause");
	system("cls");

	// PICK ONE FRONTIER AT RANDOM
	if (v.size() != 0)
	{
		std::random_shuffle(v.begin(), v.end());

		// Get random number from size of vector
		srand(time(NULL));
		int randint = rand() % v.size();

		// Randomly pop a node from the frontier vector
		Node * next = v[randint];
		v.erase(v.begin() + randint);

		// Find new frontier's visited neighbor, connect
		for (int i = 3; i >= 0; i--)
		{
			if (next->link[i] != nullptr && next->link[i]->visited == true)
			{
				joinNodes(next, next->link[i]);
				break;
			}
		}

		recursivePrims(next, nullptr, v);
	}

	/*if (n->visited)
		return;

	printMaze();
	system("cls");

	// "Visit" the current node
	n->visited = true;

	if (p != nullptr && p != n)
	{
		joinNodes(n, p);
	}

	// Make a vector of the surrounding nodes
	std::vector<Node *> surrounding;
	for (int i = 0; i < 4; i++)
	{
		if (n->link[i] != nullptr && !n->link[i]->visited)
		{
			surrounding.push_back(n->link[i]);
		}
	}

	std::random_shuffle(surrounding.begin(), surrounding.end());
	for (int i = 0; i < surrounding.size(); i++)
	{
		recursivePrims(surrounding[i], n);
	}*/
}

void Maze::randomizeDoors()
{
	Node * current = base;
	Node * leftmost = base;

	while (leftmost != nullptr)
	{
		while (current != nullptr)
		{
			int randint = rand() % 4 + 1;
			
			current->door[randint] = !current->door[randint];
			
			current = current->getRight();
		}
		leftmost = leftmost->getDown();
		current = leftmost;
	}

	/*std::vector<Node *> randVect = mazeVect;

	std::random_shuffle(randVect.begin(), randVect.end());

	for (int i = 0; i < randVect.size(); i++)
	{
		Node * n = randVect[i];
	}*/
}

void Maze::printMaze()
{
	Node * current = base;
	Node * leftmost = base;

	// Print line on top row
	while (current != nullptr)
	{
		if (current->door[0])
			std::cout << "__";

		// Do one more at the end
		if (current->getRight() == nullptr)
			std::cout << "_" << std::endl;

		current = current->getRight();
	}

	// Now iterate through whole thing
	while (leftmost != nullptr)
	{
		// Iterate through current line
		while (current != nullptr)
		{
			// If we need a horizontal and vertical line
			bool horLine = current->door[1] || (current->getDown() != nullptr && current->getDown()->door[0]);
			bool vertLine = current->door[2] || (current->getLeft() != nullptr && current->getLeft()->door[3]);

			if (vertLine)
				std::cout << "|";
			else if (horLine)
				std::cout << "_";
			else
				std::cout << " ";

			if (horLine)
				std::cout << "_";
			else
				std::cout << " ";

			// If we are at the end of the row
			if (current->getRight() == nullptr)
			{
				// Print one last | if we need a wall there
				if (current->door[3])
					std::cout << "|";

				std::cout << std::endl;
			}

			current = current->getRight();
		}
		leftmost = leftmost->getDown();
		current = leftmost;
	}
}

bool Maze::joinNodes(Node * n1, Node * n2)
{
	if (n1 == nullptr || n2 == nullptr)
		return false;

	for (int i = 0; i < 4; i++)
	{
		if (n1->link[i] == n2)
		{
			int index = 0;
			if (i == 0 || i == 2)
				index = i + 1;
			else
				index = i - 1;

			n1->door[i] = 0;
			n2->door[index] = 0;
		}
	}

	/*if (n1->getUp() == n2)
	{
		n1->upDoor = 0;
		n2->downDoor = 0;
	}
	else if (n1->getDown() == n2)
	{
		n1->downDoor = 0;
		n2->upDoor = 0;
	}
	else if (n1->getLeft() == n2)
	{
		n1->leftDoor = 0;
		n2->rightDoor = 0;
	}
	else if (n1->getRight ()== n2)
	{
		n1->rightDoor = 0;
		n2->leftDoor = 0;
	}
	else
	{
		return false;
	}*/

	return true;
}

Node * Maze::findRandomNeighbor(bool unvisited = true)
{
	return nullptr;
}