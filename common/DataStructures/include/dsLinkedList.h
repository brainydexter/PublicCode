#ifndef _DS_LINKEDLIST_H_
#define _DS_LINKEDLIST_H_

#include "defines.h"

class dsLinkedList
{
public:
	dsLinkedList(int value);
	virtual ~dsLinkedList();

	inline int getData() const { return this->data; }
	inline void setData(int value) { this->data = value; }

	inline dsLinkedList* getNext() const { return this->next; }
	inline void setNext(dsLinkedList* nextNode) { this->next = nextNode; }

protected:
	int data;
	dsLinkedList* next;
};

STATUS dsLinkedList_insert(dsLinkedList** head, int value);
void dsLinkedList_clear(dsLinkedList** head);
dsLinkedList* dsLinkedList_find(dsLinkedList* head, int value);
void dsLinkedList_print(const dsLinkedList* head, std::ostream& os);
bool dsLinkedList_loopExists(dsLinkedList* head);
bool dsLinkedList_loopDetails(dsLinkedList* head, dsLinkedList** loopNode, std::size_t& loopLength);

#endif // _DS_LINKEDLIST_H_