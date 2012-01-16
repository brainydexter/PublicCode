using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DS_HashMap
{
    /// <summary>
    /// Hashmap based on chaining
    /// </summary>
    public class HashMap
    {
        private readonly int capacity;
        private LinkedList<HashMapNode>[] arr;

        public HashMap(int capacity)
        {
            this.capacity = capacity;
            arr = new LinkedList<HashMapNode>[capacity];
        }

        /// <summary>
        /// Capacity of the array
        /// </summary>
        public int Capacity { get { return capacity; } }

        /// <summary>
        /// Insert element with key into hash table,
        /// if key does not exist in hash table
        /// otherwise raise exception for duplicate found
        /// Performance is O(1)
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        public void Insert(int key, int value)
        {
            int bucket = hashFunction(key);

            if (arr[bucket] == null)
            {
                arr[bucket] = new LinkedList<HashMapNode>();
                arr[bucket].AddFirst(new HashMapNode(key, value));
                return;
            }

            var currentNode = arr[bucket].First;

            while (currentNode != null && currentNode.Value.Key < key)
                currentNode = currentNode.Next;

            if( currentNode == null) // reached tail
            {
                // O(1)
                arr[bucket].AddLast(new HashMapNode(key, value)); // key is bigger than everyone else
            }
            else if (currentNode.Value.Key == key) // duplicate found
            {
                throw new ArgumentException(string.Format("Element with the same key: {0} exists in the hash map", key));
            }
            else if (System.Object.ReferenceEquals(arr[bucket].First, currentNode))
            {
                // O(1)
                arr[bucket].AddFirst(new HashMapNode(key, value));  // key is less than the head
            }
            else
            {
                // O(1)
                arr[bucket].AddBefore(currentNode, new HashMapNode(key, value));
            }

        }

        /// <summary>
        /// Returns true if element with key is found in Hashmap
        /// Performance is O(1)
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        public bool Search(int key) 
        { 
            int bucket = hashFunction(key);

            if (arr[bucket] == null)
                return false;

            var currentNode = arr[bucket].First;

            while (currentNode != null)
            {
                if (currentNode.Value.Key == key)
                    return true;

                if (currentNode.Value.Key > key)       // early exit since nodes are ordered by keys
                    return false;
                else
                    currentNode = currentNode.Next;
            }

            return false;
        }

        /// <summary>
        /// Removes element with key, in hashmap, if element exists.
        /// Otherwise, an exception is thrown.
        /// Performance is O(1)
        /// </summary>
        /// <param name="key"></param>
        public void Remove(int key) 
        {
            if (!Search(key))
                throw new KeyNotFoundException(string.Format("Key: {0} not found in hashmap", key));

            int bucket = hashFunction(key);
            var currentNode = arr[bucket].First;

            while (currentNode != null)
            {
                if (currentNode.Value.Key == key)
                    break;

                currentNode = currentNode.Next;
            }

            arr[bucket].Remove(currentNode);
        }

        /// <summary>
        /// Returns the bucket index for this key
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        private int hashFunction(int key)
        {
            return key % this.capacity;
        }

        public int Count()
        {
            int count = 0;

            foreach (var node in arr)
            {
                if (node != null)
                    count += node.Count;
            }
            return count;
        }

        private class HashMapNode
        {
            private int key;
            private int value;

            public HashMapNode(int key, int val)
            {
                this.key = key;
                this.value = val;
            }

            public int Key { get { return key; } }
            public int Value { get { return value; } }

            // evaluate for equality of value
            public override bool Equals(object obj)
            {
                if (obj == null)
                    return false;
                
                HashMapNode node = obj as HashMapNode;
                if (node == null)
                    return false;

                return node.Key == this.Key && node.Value == this.Value;
            }

            public override int GetHashCode()
            {
                return base.GetHashCode();
            }
        }
    }
}
