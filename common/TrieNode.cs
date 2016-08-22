using UnityEngine;
using System;
using System.Diagnostics;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/*
 * Optimizations:
 * Memory:
 *  1. Do not allocate children for leaf node - Done
 *  2. Allocate using List<index, node> - Done
 *  3. use constant TrieNodes for last letter - doesnt work since it corrupts existing paths
 *  4. idea to decrease memory 
 *      - use TrieNode directly and not keyValue
 *      - replace all duplicate nodes with one node
 *       - post process all nodes to find duplicates
 */
public class TrieNode : IWordDictionaryDS {

    public TrieNode(char c){
        this.eow = false;

        value = (byte)(c - 'A');
    }

    // inserts the word intro trie
    // O(word.Length)
    public void Insert(string word){
        // calculate wordLen so its not done everytime word.length is called
        int wordLen = word.Length;

		if (wordLen < Constants.MIN_WORD_LENGTH)
            return;
        
        TrieNode current = this;

        for (int i = 0; i < wordLen; ++i) {

            // process ith letter of word
            char c = word [i];

            // index of letter
            int index = c - 'A';

            UnityEngine.Debug.Assert (index >= 0 && index < 26, "Trying to add invalid word: " + word + " at letter: " + c);

            TrieNode child = null;
            if (!current.childExists (index, ref child)) {
                child = new TrieNode (c);
                current.insertChild (index, child);
            }

            // child letter exists
            // time to process next letter (which is represented by child)
            current = child;
        }

        // when control reaches here, end of word has been reached
        current.eow = true;
    }

    // Searches for word/pattern in trie
    public bool Search(string word, bool patternOnly = false){
        TrieNode current = this;

        int wordLen = word.Length;
        for (int i = 0; i < wordLen; i++) {
            // process ith letter of word
            char c = word [i];

            // index of letter
            int index = c - 'A';

            //            // find child node representing this letter
            TrieNode child = null;
            if (!current.childExists (index, ref child)) {
                return false;
            }

            // if found, continue to find next letter
            // which is represented by child
            current = child;
        }

        if (patternOnly)
            return true;

        return current.eow;
    }

    private bool childExists(int index, ref TrieNode child){
        child = null;

        if (this.children == null)
            return false;
        
        for (int i = 0; i < this.children.Count; ++i) {
            if (this.children [i].value == index) {
                child = this.children [i];
                return true;
            }
        }

        child = null;
        return false;
  
    }

    private void insertChild(int index, TrieNode child){
        if(this.children == null)
            this.children = new List<TrieNode> ();

        this.children.Add (child);
    }

    // does the current node denote end of word
    private bool eow;

    public byte value { get; private set; }

    // can only contain a-z letters.
    private List<TrieNode> children = null;
}
