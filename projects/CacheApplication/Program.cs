using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CacheApplication
{
    class Node<KeyT, ValT>
    {
        private KeyT key;
        private ValT value;
        private DateTimeOffset timeStamp;

        internal void Refresh()
        {
            timeStamp = DateTimeOffset.Now;
        }

        public ValT Info { get { return value; } }

        public Node(KeyT key, ValT value)
        {
            this.key = key;
            this.value = value;

            Refresh();
        }

        public DateTimeOffset TimeStamp { get { return timeStamp; } }

        public KeyT Key { get { return key; } }

        public override string ToString()
        {
            return string.Format("{0} => {1} : {2} ", this.Key, this.Info, this.TimeStamp);
        }
    }

    class CacheLRU<KeyT,ValT> : IEnumerable<KeyValuePair<KeyT, ValT> >
    {
        LinkedList<Node<KeyT,ValT>> mLinkedList;
        Dictionary<KeyT, LinkedListNode<Node<KeyT,ValT>>> mDictionary;
        private readonly int timeOut;

        public CacheLRU(int timeout)
        {
            this.timeOut = timeout;

            mDictionary = new Dictionary<KeyT, LinkedListNode<Node<KeyT,ValT>>>();
            mLinkedList = new LinkedList<Node<KeyT,ValT>>();
        }

        /// <summary>
        /// O(1)
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        public ValT Read(KeyT key)
        {
            Console.Out.WriteLine(string.Format("Read() Executing for {0}, ", key));

            LinkedListNode<Node<KeyT, ValT>> linkedNode;

            // assume key exists
            if (mDictionary.TryGetValue(key, out linkedNode))     // O(1)
            {
                linkedNode.Value.Refresh();   // O(1)

                mLinkedList.Remove(linkedNode);   // O(1) since specific node is removed
                mLinkedList.AddLast(linkedNode); // O(1)

                // update dictionary with the updated node
                mDictionary[key] = linkedNode;    // O(1)

                return linkedNode.Value.Info;
            }
            throw new KeyNotFoundException(string.Format("Read() : Key Not found in cache: {0}", key));
        }

        public void Write(KeyT key, ValT value)
        {
            Console.Out.WriteLine(string.Format("Write() Executing for {0}, {1}", key, value));
            LinkedListNode<Node<KeyT,ValT>> linkedNode = new LinkedListNode<Node<KeyT,ValT>>(new Node<KeyT,ValT>(key, value));

            try
            {
                mDictionary.Add(key, linkedNode);    // O(1)
                mLinkedList.AddFirst(linkedNode);    // O(1)
            }
            catch (Exception)       // for adding key
            {
                Console.Out.WriteLine(string.Format("Write(): Exception: Key {0} already exists with value: {1}", key, value));
            }
        }

        public void WorkerTask()
        {
            DateTimeOffset currentTIme = DateTimeOffset.Now;
            Console.Out.WriteLine(string.Format("WorkerTask() Executing @ {0}", currentTIme));

            LinkedListNode<Node<KeyT,ValT>> linkedNode = mLinkedList.First;
            LinkedListNode<Node<KeyT,ValT>> nextLinkedNode;

            while(linkedNode != null)
            {
                Node<KeyT, ValT> node = linkedNode.Value;
                double timeDifference = currentTIme.Subtract(node.TimeStamp).TotalMilliseconds;

                if (timeDifference > timeOut)
                {
                    nextLinkedNode = linkedNode.Next;

                    mDictionary.Remove(node.Key);
                    mLinkedList.Remove(linkedNode);
                }
                else
                    break;

                linkedNode = nextLinkedNode;
            }

            Console.Out.WriteLine("WorkerTask() Completed.");
        }

        #region IEnumerable<int> Members

        public IEnumerator<KeyValuePair<KeyT, ValT>> GetEnumerator()
        {
            foreach (var kvp in mDictionary)
                yield return new KeyValuePair<KeyT, ValT>(kvp.Key, kvp.Value.Value.Info);
        }

        #endregion

        #region IEnumerable Members

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        #endregion

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            foreach (var kvp in mDictionary)
            {
                builder.AppendLine(string.Format("{0} => {1} ", kvp.Key, kvp.Value.Value));
            }

            return builder.ToString();
        }
    }

    class Program
    {
        static int writeKey = 0;

        static void Main(string[] args)
        {
            var timeout = 1000;
            var cache = new CacheLRU<string,int>(timeout);

            writeTocache(cache);
            printCache(cache);

            Thread.Sleep(timeout);
            cache.Read("A" + 1);
            
            cache.WorkerTask();
            printCache(cache);

            writeTocache(cache);
            printCache(cache);

            Thread.Sleep(timeout);
            cache.WorkerTask();
            printCache(cache);

            Console.Out.WriteLine("Hit Any key");
            Console.ReadKey();

        }

        private static void printCache(CacheLRU<string, int> cache)
        {
            Console.Out.WriteLine();
            Console.Out.WriteLine(string.Format("Cache State at {0}: ", DateTimeOffset.Now));
            Console.Out.WriteLine(cache.ToString());
            //foreach (var entry in cache)
            //{
            //    Console.Out.WriteLine(entry);
            //}
        }

        private static void writeTocache(CacheLRU<string, int> cache)
        {
             var random = new Random((int)DateTime.Now.Ticks);

             for (int i = 0; i < 5; ++i)
             {
                 cache.Write("A" + writeKey, writeKey * 10);
                 ++writeKey;
             }

             Console.Out.WriteLine("Write() Completed.");
        }

    }

}
