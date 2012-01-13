Choice of Language: C#

A simple model for a cache is a <key, value> dictionary (like a hash_map) that may remove <key, value> pairs according to a caching policy.
Thus, when a client returns to request a value from the cache by key, the value may or may not be there even if it was inserted earlier.
 
The goal of this cache is to ensure that the most requested items are likely to still be there.
 
This exhibits the following characteristics:
- It is an “associative container” . Keys and values can be objects of arbitrary type, specified by template specifiers at cache creation time.
- The cache has a timeout value which is specified at construction time.
- When an item in the cache has not been referenced for a period exceeding the timeout value, it will be removed from the cache (i.e. LRU with a specific timeout). 
	- A worker thread is used to perform the expirations.
- The cache supports iteration of its elements. These will be in order from least recently referenced to most recently referenced.

NOTE: This does not support multi-threading yet.

ALGORITHM:
- Cache contains a Dictionary and Doubly Linked List
	- Dictionary<KeyT, LinkedListNode< Node<KeyT, ValT> >>
	- LinkedList< Node<KeyT, ValT> >
	where KeyT,ValT are types of key & value

 - LinkedList represents elements(Key, Value pair) ordered by time with Most Recently used elements at the end of LinkedList
 - Dictionary helps in O(1) read/write operations

 - ValT Read(KeyT key) operation: O(1)
  - if cache does not contain the key, raise KeyNotFoundException
  - Else
	- Read operation on a key refreshes the element's expiry time 
	- It is pushed to the end of LinkedList with unlinking from current position

- void Write(KeyT key, ValT val) : O(1)
 - create a pair with current time as timestamp
 - add pair to dictionary
 - add pair node as first element to linked list

- void WorkerTask() (Usually run in a separate thread) : O(n)
 - For all those tasks who have expired;
  - remove from dictionary and linked list
  - small optimisation:
   - since elements are sorted by time, we can do an early exit based on first false