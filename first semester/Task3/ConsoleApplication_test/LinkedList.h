#pragma once
#include "Image.h"
//Реализовать односвязный список
struct node
{
	Image *image_node;
	node *next;
	node::node()
	{
		image_node = NULL;
		next = NULL;
	}
};
class LinkedList
{
private:	
	//head of the list contains the image data
	node *head, *tail;
	int listLength;
public:
	//Default constructor creates the head node
	LinkedList();

	//Destructor de-allocates memory used by the list.
	virtual ~LinkedList(); /*throw()*/

	//Takes a node and list position as parameters.
	//Position must be between 1 and the number of data nodes
	//Returns true if the operation is successful.
	bool insertNode(node *newNode, const int const position);

	//Setter removes a node by its given position.
	//Returns true if the operation is successful.
	bool removeNode(const int const position);

	//Prints each node in the list in consecutive order,
	//starting at the head and ending at the tail.
	//Prints list data to the console.
	void printListLength();


	void insertAtFront(const node &value);
	void insertAtBack(const node &value);
	bool removeFromFront();
	bool removeFromBack();

	node* getNewNode(const node &value);
	bool isEmpty()const;
	node* GetHead(void)const;
};

