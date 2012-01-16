using DS_HashMap;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;

namespace DS_HashMapTestProject
{
    
    
    /// <summary>
    ///This is a test class for HashMapTest and is intended
    ///to contain all HashMapTest Unit Tests
    ///</summary>
    [TestClass()]
    public class HashMapTest
    {
        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        // 
        //You can use the following additional attributes as you write your tests:
        //
        //Use ClassInitialize to run code before running the first test in the class
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //Use ClassCleanup to run code after all tests in a class have run
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //Use TestInitialize to run code before running each test
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //Use TestCleanup to run code after each test has run
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion

        public HashMapTest()
        {
        }

        /// <summary>
        ///A test for Insert
        ///</summary>
        [TestMethod()]
        public void InsertTest()
        {
            var hashMap = new HashMap(11);
            hashMap.Insert(22, 0);
            hashMap.Insert(44, 1);
            hashMap.Insert(33, 2);
            hashMap.Insert(11, 3);
            Assert.AreEqual(hashMap.Count(), 4);
        }

        /// <summary>
        ///A test for Remove
        ///</summary>
        [TestMethod()]
        public void RemoveTest()
        {
            var hashMap = new HashMap(11);

            hashMap.Insert(22, 1);
            hashMap.Insert(33, 1);
            hashMap.Insert(44, 1);
            hashMap.Remove(33);

            try
            {
                hashMap.Remove(21);
            }
            catch (KeyNotFoundException exception)
            {
                Console.Out.WriteLine("Key not found for remove which doesn't exist in hashmap and hence exception raised");
            }

        }

        /// <summary>
        ///A test for Search
        ///</summary>
        [TestMethod()]
        public void SearchTest()
        {
            bool expected = true;
            var hashMap = new HashMap(11);
            hashMap.Insert(22, 1);
            hashMap.Insert(44, 1);
            
            var actual = hashMap.Search(22);
            Assert.AreEqual(expected, actual);

            expected = false;
            actual = hashMap.Search(33);
            Assert.AreEqual(expected, actual);
        }
    }
}
