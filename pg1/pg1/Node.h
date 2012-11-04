#pragma once
class Node
{
public:


	Node(void);
	Node(int from, int to);
	~Node(void);

private:

	AABB * bounds;
	int span[2];
	Node * childern[2];
};

