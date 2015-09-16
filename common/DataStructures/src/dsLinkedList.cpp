#include "dsLinkedList.h"

dsLinkedList::dsLinkedList(int value)
	: data(value), next(NULL) {}

dsLinkedList::~dsLinkedList()
{
	next = NULL;
}

STATUS dsLinkedList_insert(dsLinkedList** head, int value)
{
	if (*head == NULL)
	{
		*head = new dsLinkedList(value);
		return NO_ERR;
	}

	dsLinkedList* node = new dsLinkedList(value);

	node->setNext(*head);
	*head = node;

	return NO_ERR;
}

void dsLinkedList_clear(dsLinkedList** head)
{
	dsLinkedList *next = NULL, *current = *head;

	while(current)
	{
		next = current->getNext();

		delete current;

		current = next;
		*head = current;
	}
}

dsLinkedList* dsLinkedList_find(dsLinkedList* head, int value)
{
	while (head)
	{
		if (head->getData() == value)
		{
			return head;
		}

		head = head->getNext();
	}
	return NULL;
}

void dsLinkedList_print(const dsLinkedList* head, std::ostream& os)
{
	if(!head)
	{
		os << "Empty Linked list \n";
	}

	while (head)
	{
		os << head->getData() << " (" << head << ")";
		os << ((head->getNext() != NULL) ? " -> " : " -> .\n");

		head = head->getNext();
	}
}

bool dsLinkedList_loopExists(dsLinkedList* head)
{
	if (head == NULL)
	{
		return false;
	}

	dsLinkedList *slow = head, *fast = head;
	do
	{
		if (fast->getNext() && fast->getNext()->getNext())
		{
			fast = fast->getNext()->getNext();
		}
		else
		{
			return false;
		}

		slow = slow->getNext();

		if(slow == fast)
			return true;
	}
	while(fast != NULL);
	
	return false;
}

bool dsLinkedList_loopDetails(dsLinkedList* head, dsLinkedList** loopNode, std::size_t& loopLength)
{
	if (head == NULL)
	{
		return false;
	}

	*loopNode = NULL;
	loopLength = 0;
	bool found = false;
	
	dsLinkedList *slow = head, *fast = head;
	do
	{
		if (fast->getNext() && fast->getNext()->getNext())
		{
			fast = fast->getNext()->getNext();
		}
		else
		{
			return false;
		}

		slow = slow->getNext();

		if(slow == fast)
		{
			found = true;
			break;
		}
	}
	while(fast != NULL);
	
	if(found)
	{
		slow = head;
		while(slow != fast)
		{
			slow = slow->getNext();
			fast = fast->getNext();
			++loopLength;
		}

		*loopNode = slow;
	}

	return found;
}