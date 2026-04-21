# 1722. Minimize Hamming Distance After Swap Operations

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Depth-First Search, Union-Find &nbsp;|&nbsp; **Solved:** April 21, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 175 ms &nbsp;|&nbsp; **Memory:** 155429.7 MB

---

## Problem

You are given two integer arrays, `source` and `target`, both of length `n`. You are also given an array `allowedSwaps` where each `allowedSwaps[i] = [ai, bi]` indicates that you are allowed to swap the elements at index `ai` and index `bi` **(0-indexed)** of array `source`. Note that you can swap elements at a specific pair of indices **multiple** times and in **any** order.

The **Hamming distance** of two arrays of the same length, `source` and `target`, is the number of positions where the elements are different. Formally, it is the number of indices `i` for `0 <= i <= n-1` where `source[i] != target[i]` **(0-indexed)**.

Return _the **minimum Hamming distance** of _`source`_ and _`target`_ after performing **any** amount of swap operations on array _`source`_._

 

**Example 1:**

> **Input:** source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
> **Output:** 1
> **Explanation:** source can be transformed the following way:
> - Swap indices 0 and 1: source = [2,1,3,4]
> - Swap indices 2 and 3: source = [2,1,4,3]
> The Hamming distance of source and target is 1 as they differ in 1 position: index 3.

**Example 2:**

> **Input:** source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
> **Output:** 2
> **Explanation:** There are no allowed swaps.
> The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.

**Example 3:**

> **Input:** source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
> **Output:** 0

## Constraints

- `n == source.length == target.length`
	
- `1 <= n <= 105`
	
- `1 <= source[i], target[i] <= 105`
	
- `0 <= allowedSwaps.length <= 105`
	
- `allowedSwaps[i].length == 2`
	
- `0 <= ai, bi <= n - 1`
	
- `ai != bi`

## Hints

1. The source array can be imagined as a graph where each index is a node and each allowedSwaps[i] is an edge.
2. Nodes within the same component can be freely swapped with each other.
3. For each component, find the number of common elements. The elements that are not in common will contribute to the total Hamming distance.

---

## Intuition

The allowed swaps connect indices into **connected components**.  
Inside a component any permutation of its elements is achievable, because swaps can be performed repeatedly along the edges of the component.  
Therefore the only thing that matters is **how many of each value we have in a component**.  
If a value that appears in `target` also exists in the same component of `source`, we can place it there and avoid a mismatch.  
The minimal Hamming distance is simply the number of positions whose required value cannot be supplied by its component.

## Approach

1. **Build components** – Use a Union‑Find (Disjoint Set Union) to merge every pair in `allowedSwaps`. After processing all pairs, `find(i)` returns the component identifier (root) of index `i`.
2. **Count source values per component** – For each index `i`, increment `cnt[root(i)][source[i]]`. Here `cnt` is a map from component‑root to a frequency map of values.
3. **Match target values** – Iterate indices again:
   - Let `r = find(i)`.  
   - If `cnt[r]` contains `target[i]` with positive count, decrement the count (we can place that value inside the component).  
   - Otherwise this position is forced to differ → increment the answer.
4. Return the accumulated answer.

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(n \,\alpha(n) + m \,\alpha(n)) = O(n+m)$ | Union‑Find operations are amortized $α(n)$; we traverse the arrays once. |
| **Space**      | $O(n)$     | Parent/size arrays of DSU plus the frequency maps (total entries ≤ $n$). |

## Key Takeaways

- **Swap graph → DSU**: Converting arbitrary swap constraints into connected components lets us treat each component as a fully reorderable bag.
- **Frequency matching**: Reducing the problem to “can we supply each target value from its component?” avoids explicit permutations.
- **Path compression + union by size** guarantees near‑linear time even for $10^5$ edges.
- **Map of maps** is sufficient because the total number of stored key‑value pairs never exceeds `n`; alternative representations (e.g., `vector<unordered_map>`) are interchangeable.

## My Original Solution

```cpp
class Graph{
    public:
        vector<int> parent;
        vector<int> size;
    Graph(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i = 0;i < n;i++) parent[i] = i;
    }
    int findUltimateParent(int n){
        if(parent[n] == n) return n; 
        return parent[n] = findUltimateParent(parent[n]);
    }
    void mergeParent(int i, int j){
        int ul_i = findUltimateParent(i);
        int ul_j = findUltimateParent(j);
        if(ul_i == ul_j) return;
        if(size[ul_i] >= size[ul_j]){
            parent[ul_j] = ul_i;
            size[ul_i] += size[ul_j];
        }else{
            parent[ul_i] = ul_j;
            size[ul_j] += size[ul_i];
        }
    }
};
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        int result = 0;
        Graph g(n);
        for(auto i : allowedSwaps){
            g.mergeParent(i[0],i[1]);
        }
        unordered_map<int,unordered_map<int,int>> mpp;
        for(int i = 0;i < n;i++){
            int ul_i = g.findUltimateParent(i);
            mpp[ul_i][source[i]]++;
        }
        for(int i = 0;i < n;i++){
            int ul_i = g.findUltimateParent(i);
            if(mpp[ul_i][target[i]] > 0) mpp[ul_i][target[i]]--;
            else result++;
        }
        return result;
    }
};
```

## Professional Refactor

```cpp
// language: cpp
class DSU {
    vector<int> parent, sz;
public:
    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

class Solution {
public:
    int minimumHammingDistance(vector<int>& source,
                               vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        DSU dsu(n);
        for (const auto& p : allowedSwaps) dsu.unite(p[0], p[1]);

        // component → value → frequency
        unordered_map<int, unordered_map<int, int>> compCnt;
        for (int i = 0; i < n; ++i) {
            int r = dsu.find(i);
            ++compCnt[r][source[i]];
        }

        int mismatches = 0;
        for (int i = 0; i < n; ++i) {
            int r = dsu.find(i);
            auto& freq = compCnt[r];
            if (freq[target[i]] > 0) {
                --freq[target[i]];
            } else {
                ++mismatches;
            }
        }
        return mismatches;
    }
};
```

## Code Walkthrough

- **DSU constructor** initializes `parent[i] = i` and `sz[i] = 1`. `iota` fills the parent array in linear time.
- **find** uses path compression: `parent[x] = find(parent[x])` collapses the tree, guaranteeing amortized $α(n)$ per call.
- **unite** merges two roots, always attaching the smaller tree under the larger (`sz`), which keeps the depth shallow.
- **Building `compCnt`**: for each index we locate its root `r` and increment the frequency of `source[i]` inside `compCnt[r]`. This creates a multiset of values that can be freely rearranged within the component.
- **Matching phase**: for each index we again locate its component. If `target[i]` exists in the component’s multiset (`freq[target[i]] > 0`), we consume one occurrence (`--freq`). Otherwise the value cannot be supplied → we count a mismatch.
- The final `mismatches` is the minimal Hamming distance after any sequence of allowed swaps.
