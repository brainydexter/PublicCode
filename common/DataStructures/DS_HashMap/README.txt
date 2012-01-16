Language: C#
Compiler/Platform: .NET 4.0
IDE: Visual Studio 2010

Objective: Implement hash map using chaining

other resources: 
- http://www.gamedev.net/page/resources/_/technical/game-programming/an-introduction-to-hash-tables-with-chaining-r2066
- http://en.wikipedia.org/wiki/Hash_table#Separate_chaining

Assumption: 
- int keys for simplicity. Otherwise use a hash function for other types!

Algorithm:

(underlying data structure:)
DoublyLinkedList[SIZE] arr;

Insert(key, value): O(1)
 - find bucket to insert this key; using hash function
 - insert the (key, value) element in correct position in the linked list (such that elements are ordered)
 - if key already exists in the linked list: raise exception

 Search(key): O(1)
 - find bucket for this key; using hash function
 - search for this key in the linkedlist: arr[bucket]
  - since elements are ordered, one can early exit with a false; if the key < currentNode.key

Remove(key): O(1)
 - search if element is present in hashmap. 
  - if not - raise exception
 - iterate through the linkedlist: arr[bucket] to find the element with currentNode.key == key
 - remove currentNode from collection



