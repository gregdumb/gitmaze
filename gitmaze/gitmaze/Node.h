#pragma once

class Node
{
private:
	Node * Up;
	Node * Down;
	Node * Left;
	Node * Right;

public:

	Node * link[4];
	int door[4] = { 0, 0, 0, 0 };

	int upDoor, downDoor, leftDoor, rightDoor;

	int index = 0;

	bool visited = false;
	bool inlist = false;

	Node(int, int, int, int);

	void setUp(Node * n)
	{
		link[0] = n;
	}

	void setDown(Node * n)
	{
		link[1] = n;
	}

	void setLeft(Node * n)
	{
		link[2] = n;
	}

	void setRight(Node * n)
	{
		link[3] = n;
	}

	Node * getUp()
	{
		return link[0];
	}

	Node * getDown()
	{
		return link[1];
	}

	Node * getLeft()
	{
		return link[2];
	}

	Node * getRight()
	{
		return link[3];
	}
};

Node::Node(int upD, int downD, int leftD, int rightD)
{
	Up = nullptr;
	Down = nullptr;
	Left = nullptr;
	Right = nullptr;

	door[0] = upD;
	door[1] = downD;
	door[2] = leftD;
	door[3] = rightD;
}