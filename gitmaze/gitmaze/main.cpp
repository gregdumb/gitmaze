#include <iostream>
#include <vector>
#include "stdlib.h"
#include "time.h"
#include "Maze.h"

int main()
{

	Maze * myMaze = new Maze(10);
	myMaze->printMaze();

	system("pause");

	/*
	Node * base = new Node(0, 0, 0, 0);

	Node * current = base;

	std::vector<Node*> nodeVect;
	nodeVect.push_back(base);

	const int rowWidth = 10;
	const int numNodes = rowWidth * rowWidth;

	int currentRowWidth = 1;

	for (int i = 0; i < numNodes - 1; i++)
	{
		Node * newNode = new Node(0, 0, 0, 0);
		nodeVect.push_back(newNode);

		if(currentRowWidth < rowWidth)
		{
			current->Right = newNode;
			newNode->Left = current;
			if (current->Up != nullptr && current->Up->Right != nullptr)
			{
				newNode->Up = current->Up->Right;
				current->Up->Right->Down = newNode;
			}
			currentRowWidth++;
		}
		else
		{
			currentRowWidth = 1;
			current = base;
			while (current->Down != nullptr)
			{
				current = current->Down;
			}

			current->Down = newNode;
			newNode->Up = current;
		}

		current = newNode;
	}

	// PRINT FROM GRAPH
	current = base;
	Node * leftmost = base;

	while (leftmost != nullptr)
	{
		while (current != nullptr)
		{
			
			std::cout << "[";

			if (current->Left != nullptr)
				std::cout << "<";
			else
				std::cout << " ";

			if (current->Down != nullptr)
				std::cout << "v";
			else
				std::cout << " ";

			if (current->Up != nullptr)
				std::cout << "^";
			else
				std::cout << " ";

			if (current->Right != nullptr)
				std::cout << ">";
			else
				std::cout << " ";

			std::cout << "]";

			if (current->Right == nullptr)
				std::cout << std::endl;
			
			current = current->Right;
		}
		leftmost = leftmost->Down;
		current = leftmost;
	}

	std::cout << std::endl;


	// PRINT FROM VECTOR
	for (int i = 0; i < nodeVect.size(); i++)
	{
		std::cout << "[";

		if (nodeVect[i]->Up != nullptr)
			std::cout << "^";
		else
			std::cout << " ";

		if (nodeVect[i]->Down != nullptr)
			std::cout << "v";
		else
			std::cout << " ";

		if (nodeVect[i]->Left != nullptr)
			std::cout << "<";
		else
			std::cout << " ";

		if (nodeVect[i]->Right != nullptr)
			std::cout << ">";
		else
			std::cout << " ";

		std::cout << "]";

		if ((i + 1) % rowWidth == 0)
			std::cout << std::endl;
	}

	for (int i = 0; i < nodeVect.size(); i++)
	{
		if (nodeVect[i]->Up == nullptr)
			nodeVect[i]->upDoor = 1;

		if (nodeVect[i]->Down == nullptr)
			nodeVect[i]->downDoor= 1;

		if (nodeVect[i]->Left == nullptr)
			nodeVect[i]->leftDoor = 1;

		if (nodeVect[i]->Right == nullptr)
			nodeVect[i]->rightDoor = 1;
	}

	std::cout << std::endl;

	// Randomize doors
	srand(time(NULL));
	for (int i = 0; i < nodeVect.size(); i++)
	{
		Node * n = nodeVect[i];
		int randint = 0;

		/*if (n->Right != nullptr)
		{
			n->rightDoor = rand() % 2 - 1;
		}*//*

		switch (rand() % 4 + 1)
		{
		case 1:
			n->upDoor = 1;
			break;
		case 2:
			n->downDoor = 1;
			break;
		case 3: 
			n->leftDoor = 1;
			break;
		default:
			n->rightDoor = 1;
			break;
		}

	}

	// Print out doors
	for (int i = 0; i < nodeVect.size(); i++)
	{
		Node * n = nodeVect[i];
		// If we need a horizontal line on the bottom
		bool horLine = n->downDoor || (n->Down != nullptr && n->Down->upDoor);

		if (n->leftDoor)
			std::cout << "|";
		else if (horLine)
			std::cout << "_";
		else
			std::cout << " ";

		if (horLine)
			std::cout << "_";
		else
			std::cout << " ";

		if (n->rightDoor)
			std::cout << "|";
		else if (horLine)
			std::cout << "_";
		else
			std::cout << " ";

		if ((i + 1) % rowWidth == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;

	system("pause");*/
}