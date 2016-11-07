#include <iostream>
#include <vector>
#include "stdlib.h"
#include "time.h"
#include "Maze.h"

int main()
{
	int w = 0;

	std::cout << "How wide do you want your maze? ";
	std::cin >> w;
	std::cout << std::endl;

	Maze * myMaze = new Maze(w);
	myMaze->printMaze();
	myMaze->printSolution();

	system("pause");
}