# 2452. Words Within Two Edits of Dictionary

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, String, Trie &nbsp;|&nbsp; **Solved:** April 22, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 66 ms &nbsp;|&nbsp; **Memory:** 62730.5 MB

---

## Problem

You are given two string arrays, `queries` and `dictionary`. All words in each array comprise of lowercase English letters and have the same length.

In one **edit** you can take a word from `queries`, and change any letter in it to any other letter. Find all words from `queries` that, after a **maximum** of two edits, equal some word from `dictionary`.

Return_ a list of all words from _`queries`_, __that match with some word from _`dictionary`_ after a maximum of **two edits**_. Return the words in the **same order** they appear in `queries`.

 

**Example 1:**

> **Input:** queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
> **Output:** ["word","note","wood"]
> **Explanation:**
> - Changing the 'r' in "word" to 'o' allows it to equal the dictionary word "wood".
> - Changing the 'n' to 'j' and the 't' to 'k' in "note" changes it to "joke".
> - It would take more than 2 edits for "ants" to equal a dictionary word.
> - "wood" can remain unchanged (0 edits) and match the corresponding dictionary word.
> Thus, we return ["word","note","wood"].

**Example 2:**

> **Input:** queries = ["yes"], dictionary = ["not"]
> **Output:** []
> **Explanation:**
> Applying any two edits to "yes" cannot make it equal to "not". Thus, we return an empty array.

## Constraints

- `1 <= queries.length, dictionary.length <= 100`
	
- `n == queries[i].length == dictionary[j].length`
	
- `1 <= n <= 100`
	
- All `queries[i]` and `dictionary[j]` are composed of lowercase English letters.

## Hints

1. Try brute-forcing the problem.
2. For each word in queries, try comparing to each word in dictionary.
3. If there is a maximum of two edit differences, the word should be present in answer.

---

## Intuition

The “aha!” moment is to **search the dictionary as a prefix tree (Trie) while simultaneously counting mismatches**.  
Because every word has the same length, we can walk character‑by‑character down the Trie.  
Whenever the current character differs from the query’s character we consume one edit.  
If the edit count ever exceeds 2 we prune that branch immediately.  
Thus we never have to generate all possible edited strings; the Trie itself discards impossible paths, giving us an implicit “edit‑distance‑≤ 2” check in linear time per query.

## Approach

1. **Build a Trie** from all words in `dictionary`.  
   Each node stores 26 child pointers and a boolean `isEnd`.

2. **Depth‑first search** (`dfs`) for a single query:  
   * Parameters – current index `i`, accumulated edit count `cnt`, current Trie node.  
   * If `cnt > 2` → return `false` (prune).  
   * If `i == word length` → return `node->isEnd` (exact match reached).  
   * For every existing child `c` (0 … 25):  
     * If `c` equals the query’s character → recurse with same `cnt`.  
     * Else → recurse with `cnt + 1`.  
   * Short‑circuit as soon as any recursive call returns `true`.

3. Iterate over `queries`; keep a query if `dfs(query, 0, 0, root)` returns `true`.

## Complexity Analysis

|                | Complexity                              | Reason                                                                                     |
|----------------|----------------------------------------|--------------------------------------------------------------------------------------------|
| **Time**       | $O(d \cdot n + q \cdot 26^{2} \cdot n)$ | Building the Trie: $d$ words × length $n$. <br>For each query we explore at most 2 mismatches → at most $\binom{n}{0}25^{0} + \binom{n}{1}25^{1} + \binom{n}{2}25^{2} = O(26^{2}\,n)$ nodes. |
| **Space**      | $O(d \cdot n)$                         | One Trie node per character of every dictionary word.                                      |

*Here $d = |\text{dictionary}|$, $q = |\text{queries}|$, $n =$ word length (all equal).*

## Key Takeaways

- **Trie + bounded edit count** replaces the naïve “generate all 2‑edit variants” (which would be $O(25^{2} n)$ per query) with a single guided walk that stops early.
- **Pruning on edit budget** (`cnt > 2`) is crucial; without it the DFS would explode to $26^{n}$.
- Checking `node->isEnd` **before** recursing further allows early acceptance when the remaining suffix matches exactly, saving work for long words.
- Using **short‑circuit logical OR** (`if (found) break;`) prevents unnecessary recursion once a valid path is discovered.

## My Original Solution

```cpp
class TrieNode{
    public:
        vector<TrieNode*> child;
        bool isEnd;
        TrieNode(){
            child = vector<TrieNode*>(26, nullptr);
            isEnd = false;
        }
};
class Trie{
    public:
        TrieNode* root;
        Trie(){
            root = new TrieNode();
        }
        void insert(string s){
            TrieNode* root_node = root;
            for(char c: s){
                int ind = c-'a';
                if(root_node->child[ind] == nullptr){
                    root_node->child[ind] = new TrieNode();
                }
                root_node = root_node->child[ind];
            }
            root_node->isEnd = true;
        }
        bool dfs(string s,int ind,int count, TrieNode* root_node,int maxLimit){
            if(count > maxLimit) return false;
            bool isPossible = false;
            int i = s[ind] - 'a';
            if(root_node->isEnd == true) return true;
            for(int j = 0;j < 26 && !isPossible;j++){
                if(root_node->child[j] != nullptr){
                    if(i == j) isPossible |= dfs(s,ind+1,count, root_node->child[j],maxLimit);
                    else isPossible |= dfs(s,ind+1,count+1, root_node->child[j],maxLimit);
                }
            }
            return isPossible;
        }
        bool callDFS(string s, int maxLimit){
            return dfs(s,0,0,root,maxLimit);
        }
};
class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        Trie trie;
        for(string s : dictionary){
            trie.insert(s);
        }
        vector<string> res;
        for(string s: queries){
            if(trie.callDFS(s, 2)){
                res.push_back(s);
            }
        }
        return res;
    }
};
```

## Professional Refactor

```cpp
```cpp
#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    array<TrieNode*, 26> child{};
    bool isEnd = false;

    TrieNode() {
        child.fill(nullptr);
    }
};

class Trie {
    TrieNode* root = new TrieNode();

    // Recursive helper that returns true if a word in the trie can be matched
    // with at most `maxEdits` mismatches.
    bool dfs(const string& word, int pos, int edits,
             TrieNode* node, int maxEdits) const {
        if (edits > maxEdits) return false;          // budget exceeded
        if (pos == (int)word.size()) return node->isEnd; // reached end of word

        int cur = word[pos] - 'a';
        for (int c = 0; c < 26; ++c) {
            TrieNode* nxt = node->child[c];
            if (!nxt) continue;
            // If characters match, keep the same edit count; otherwise consume one.
            if (dfs(word, pos + 1, edits + (c != cur), nxt, maxEdits))
                return true;                         // early exit on success
        }
        return false;
    }

public:
    // Insert a dictionary word into the trie.
    void insert(const string& word) {
        TrieNode* cur = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!cur->child[idx]) cur->child[idx] = new TrieNode();
            cur = cur->child[idx];
        }
        cur->isEnd = true;
    }

    // Public wrapper for the bounded‑edit DFS.
    bool matchesWithinEdits(const string& word, int maxEdits) const {
        return dfs(word, 0, 0, root, maxEdits);
    }
};

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        Trie trie;
        for (const string& w : dictionary) trie.insert(w);

        vector<string> ans;
        for (const string& q : queries) {
            if (trie.matchesWithinEdits(q, 2))
                ans.push_back(q);
        }
        return ans;
    }
};
```
```

## Code Walkthrough

- **Trie construction (`insert`)** – walks the characters of a dictionary word, creating missing nodes on‑the‑fly; marks the terminal node with `isEnd = true`.
- **`dfs` signature** – `pos` is the current index in the query, `edits` the number of mismatches so far, `node` the current Trie node, `maxEdits` the allowed budget (2).  
  The base cases handle budget overflow and reaching the end of the word.
- **Branching loop** – iterates only over existing children (`if (!nxt) continue;`).  
  The expression `edits + (c != cur)` succinctly adds one edit when the letters differ.
- **Early termination** – as soon as a recursive call returns `true`, the function returns `true` without exploring remaining branches, dramatically cutting work for successful matches.
- **Public query check (`matchesWithinEdits`)** – hides the recursion details; the `Solution` class simply calls it for each query and collects the passing ones.
