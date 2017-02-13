#include "LinkedList.h"

LinkedList::LinkedList() :listLength(0), head(NULL), tail(NULL)
{
	std::cout << "\nEntering constructor..." << std::endl;
	std::cout << "Success: head node created. listLength set to 0." << std::endl;
}
LinkedList::~LinkedList()
{
	if (!isEmpty()) //If list isn't empty
	{
		std::cout << "Destroying nodes...\n";
		node * currentPtr = head;
		node *tempPtr;
		while (currentPtr != 0)
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete tempPtr;
			listLength--;
		}//end while
	}//end if
}
void LinkedList::insertAtFront(const node &value)
{
	std::cout << "Entering insertNode ..." << std::endl;
	node *newPtr = getNewNode(value);
	if (isEmpty()) //list is empty
	{
		head = tail = newPtr;
		listLength++;
	}
	else
	{
		newPtr->next = head;
		head = newPtr;
		listLength++;
	}
	std::cout << "Success: added '" << &value << "' and size of the list is " << listLength << ".\n";
}// end of insertAtFront
void LinkedList::insertAtBack(const node &value)
{
	std::cout << "Entering insertNode ..." << std::endl;
	node *newPtr = getNewNode(value);
	if (isEmpty()) //list is empty
	{
		head = tail = newPtr;
		listLength++;
	}
	else
	{
		tail->next = newPtr;
		tail = newPtr;
		listLength++;
	}
	std::cout << "Success: added '" << &value << "' and size of the list is " << listLength << ".\n";
}// end of insertAtBack
bool LinkedList::insertNode(node* newNode, const int const position)
{
	std::cout << "Entering insertNode ..." << std::endl;
	node *newPtr = getNewNode(*newNode);
	if ((position < 0) || (position > listLength + 1))
	{
		std::cout << "Error: the given position is out of range." << std::endl;
		return false;
	}
	if (!head)
	{
		head = newPtr;
		listLength++;
		std::cout << "Success: added '" << newNode << "' to position " << position << ".\n";
		std::cout << "listLength = " << listLength << std::endl;
		return true;
	}
	node *after_me = head;
	int count = 0;

	while (after_me)
	{
		if (count == position)
		{
			newPtr->next = after_me->next;
			after_me->next = newPtr;
			listLength++;
			std::cout << "Success: added newNode to position " << position << " .\n";
			std::cout << "listLength = " << listLength << std::endl;
			return true;
		}
		after_me = after_me->next;
		count++;
	}	
	std::cout << "Error: node wasn't added to list!";
	delete newPtr;
	return false;
}
bool LinkedList::removeFromFront()
{
	if (isEmpty())
	{
		return false;
	}
	else
	{
		node *tempPtr = head;
		if (head == tail)
		{
			head = tail = 0;
			listLength = 0;
		}
		else
		{
			head = head->next;
			listLength--;
		}
		delete tempPtr;
		std::cout << "Success: node was deleted." << std::endl;
		std::cout << "ListLength = " << listLength << std::endl;
		return true;
	}
}
bool LinkedList::removeFromBack()
{
	if (isEmpty())
	{
		return false;
	}
	else
	{
		node *tempPtr = tail;
		if (head == tail)
		{
			head = tail = 0;
			listLength = 0;
		}
		else
		{
			node* currentPtr = head;
			while (currentPtr->next != tail)
			{
				currentPtr = currentPtr->next;
			}
			tail = currentPtr;
			currentPtr->next = 0;
			listLength--;
		}
		delete tempPtr;
		std::cout << "Success: node was deleted." << std::endl;
		std::cout << "ListLength = " << listLength << std::endl;
		return true;
	}
}
bool LinkedList::removeNode(const int const position)
{
	if ((position <= 0) || (position > listLength + 1))
	{
		std::cout << "Error: the given position is out of range." << std::endl;
		return false;
	}
	if (!head->next)
	{
		std::cout << "There is nothing to remove." << std::endl;
		return false;
	}
	int count = 0;
	node *after_me = head;
	node *target_node = after_me->next;
	while (after_me)
	{
		if (count == position)
		{
			target_node = after_me->next;
			after_me->next = after_me->next->next;
			delete target_node;
			listLength--;
			std::cout << "Success: node at position " << position << " was deleted." << std::endl;
			std::cout << "ListLength = " << listLength << std::endl;
		}
		after_me = after_me->next;
		count++;
	}
	std::cout << "Error: nothing was removed from the list." << std::endl;
	return false;
}
node* LinkedList::getNewNode(const node &value)
{
	return new node(value);
}// end of getNewNode
bool LinkedList::isEmpty()const
{
	return head == NULL;
}//end of isEmpty
void LinkedList::printListLength()
{
	node *after_me = head;
	while (after_me)
	{
		after_me->image_node->show();
		after_me = after_me->next;
	}
}
node* LinkedList::GetHead(void)const
{
	return head;
}