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

The crucial observation is that we only need to know **whether** a dictionary word can be reached within two character changes, not *how* to transform it.  
A Trie stores all dictionary words sharing common prefixes in a single tree. While walking down the Trie we can keep a running edit count; as soon as the count exceeds 2 we prune the whole subtree because any continuation would need even more edits.  
Thus the problem reduces to a bounded‑depth search on the Trie, where the bound is the edit budget (2). This turns the naïve $O(|queries|\cdot|dictionary|\cdot n)$ comparison into a prefix‑aware search that stops early for mismatching branches.

## Approach

1. **Build a Trie** from all words in `dictionary`.  
2. For each `query` word, invoke a depth‑first search (`dfs`) on the Trie:  
   - Parameters: current index `pos` in the query, current node, and the number of edits used so far.  
   - **Prune** if `edits > 2`.  
   - If the node marks the end of a dictionary word, we have found a match (return `true`).  
   - Otherwise, iterate over all existing child edges (`'a'`‑`'z'`).  
     * If the child character equals `query[pos]`, recurse without increasing `edits`.  
     * If it differs, recurse with `edits+1`.  
3. If any recursion returns `true`, the query word is added to the answer list.  
4. Return the collected words preserving the original order of `queries`.

## Complexity Analysis

|                | Complexity                               | Reason                                                                                     |
|----------------|------------------------------------------|--------------------------------------------------------------------------------------------|
| **Time**       | $O(q \cdot n \cdot 26^{\,2}) = O(qn)$    | For each of the $q$ queries we traverse at most $n$ positions; at most two mismatches allow exploring up to $26$ alternatives per mismatch, giving a constant factor $26^2$. |
| **Space**      | $O(m \cdot n)$                           | The Trie stores every dictionary character once; $m$ is the number of dictionary words, each of length $n$. |
| **Auxiliary**  | $O(n)$                                   | Recursion depth is bounded by the word length $n$.                                         |

## Key Takeaways

- **Trie‑guided pruning**: By storing the dictionary in a Trie we can abort entire sub‑trees once the edit budget is exceeded, dramatically cutting the search space.  
- **Edit budget as a DFS state**: Carrying the current edit count through recursion lets us enforce the “≤ 2 edits” constraint without extra DP tables.  
- **Early acceptance**: As soon as a Trie node marked `isEnd` is reached, we can stop exploring deeper characters—even if the remaining suffix differs—because the word lengths are equal.  
- **Constant‑factor bound**: With a maximum of two edits, the branching factor is limited to $26$ per mismatch, turning an exponential‑looking search into a linear‑time check per query.

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
// Language: C++
#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    array<TrieNode*, 26> child{};
    bool isEnd = false;

    TrieNode() { child.fill(nullptr); }
};

class Trie {
    TrieNode* root = new TrieNode();

    // Depth‑first search with edit budget.
    bool dfs(const string& word, int pos, int edits, TrieNode* node, int limit) const {
        if (edits > limit) return false;               // budget exceeded
        if (node->isEnd) return true;                  // reached a dictionary word
        if (pos == (int)word.size()) return false;     // reached end without match

        int cur = word[pos] - 'a';
        for (int c = 0; c < 26; ++c) {
            TrieNode* nxt = node->child[c];
            if (!nxt) continue;
            // Same character → no extra edit, else +1 edit.
            if (dfs(word, pos + 1, edits + (c != cur), nxt, limit))
                return true;                           // early exit on first success
        }
        return false;
    }

public:
    void insert(const string& s) {
        TrieNode* node = root;
        for (char ch : s) {
            int idx = ch - 'a';
            if (!node->child[idx]) node->child[idx] = new TrieNode();
            node = node->child[idx];
        }
        node->isEnd = true;
    }

    // Public wrapper: can we match `s` within `maxEdits`?
    bool canMatch(const string& s, int maxEdits) const {
        return dfs(s, 0, 0, root, maxEdits);
    }
};

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        Trie trie;
        for (const string& w : dictionary) trie.insert(w);

        vector<string> ans;
        ans.reserve(queries.size());
        for (const string& q : queries) {
            if (trie.canMatch(q, 2)) ans.push_back(q);
        }
        return ans;
    }
};
```

## Code Walkthrough

- **Trie construction (`insert`)** – creates a path for every dictionary word; `isEnd` flags complete words.  
- **`dfs` signature** – `pos` (current index in the query), `edits` (edits used so far), `node` (current Trie node), `limit` (fixed to 2).  
- **Pruning** – `if (edits > limit) return false;` cuts off any branch that already needs more than two changes.  
- **Early success** – as soon as `node->isEnd` is true we return `true`; the remaining suffix can be ignored because all words share the same length.  
- **Branch exploration** – iterate over the 26 possible children. The expression `edits + (c != cur)` adds an edit only when the character differs, keeping the edit count accurate without extra conditionals.  
- **Early return inside the loop** – the first successful child terminates the search, preventing unnecessary work.  
- **`canMatch` wrapper** – hides recursion details from the caller; the outer loop in `twoEditWords` simply checks each query against the Trie with the fixed budget of 2.
