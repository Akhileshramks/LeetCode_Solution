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

The allowed swaps create an **undirected graph** on the indices of `source`.  
All indices that belong to the same connected component can be freely permuted, because any sequence of swaps inside the component can realize any permutation. Consequently, the only thing that matters for the Hamming distance is **how many values of `target` can be matched by the multiset of `source` values inside each component**.  
If a `target[i]` value exists in the component’s `source` multiset, we can place it at position `i`; otherwise a mismatch is inevitable. Thus the problem reduces to:

1. Find the connected components induced by `allowedSwaps`.  
2. For each component, compare the frequency of values in `source` with those required by `target`.

The Union‑Find (Disjoint Set Union, DSU) data structure gives us exactly this component decomposition in almost linear time.

---

## Approach

1. **Build DSU** for `n` indices.  
   For every pair `[a, b]` in `allowedSwaps` call `union(a, b)`.

2. **Collect source frequencies per component**  
   * Iterate `i = 0 … n‑1`  
   * `root = find(i)`  
   * Increment `freq[root][source[i]]`.

3. **Match target values**  
   * Initialise `answer = 0`.  
   * Iterate `i = 0 … n‑1` again  
   * `root = find(i)`  
   * If `freq[root][target[i]] > 0` decrement the count (a match is possible).  
   * Else `answer++` (this position will stay mismatched).

4. Return `answer`.

---

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(n \,\alpha(n) + m \,\alpha(n)) = O(n + m)$ | DSU operations are amortised $O(\alpha(n))$; two linear scans over the arrays. |
| **Space**      | $O(n)$ | `parent`, `size` arrays of DSU and the frequency map storing at most one entry per index. |

($\alpha$ is the inverse Ackermann function, practically constant.)

---

## Key Takeaways

- **Component‑wise freedom**: Any set of allowed swaps partitions indices into components where values can be arbitrarily rearranged; the global optimum is the sum of optimal local matches.
- **Frequency matching** instead of explicit permutation: Counting how many required values exist in each component yields the minimal Hamming distance without constructing the actual permutation.
- **DSU as a bridge** between graph constraints and array manipulation: Union‑Find converts the swap list into component identifiers in near‑linear time.
- **Space‑efficient counting**: A hash map per component (`unordered_map<int,int>`) stores only values that actually appear, keeping memory proportional to `n`.

---

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
// 1722. Minimize Hamming Distance After Swap Operations
// ----------------------------------------------------
// Union‑Find (DSU) + per‑component frequency counting
class DSU {
public:
    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Find with path compression
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    // Union by size
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }

private:
    vector<int> parent;
    vector<int> sz;
};

class Solution {
public:
    int minimumHammingDistance(vector<int>& source,
                               vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {
        const int n = source.size();
        DSU dsu(n);

        // 1️⃣ Build connectivity
        for (const auto& p : allowedSwaps) {
            dsu.unite(p[0], p[1]);
        }

        // 2️⃣ Frequency of source values inside each component
        unordered_map<int, unordered_map<int, int>> compFreq;
        for (int i = 0; i < n; ++i) {
            int root = dsu.find(i);
            ++compFreq[root][source[i]];
        }

        // 3️⃣ Try to satisfy target values
        int mismatches = 0;
        for (int i = 0; i < n; ++i) {
            int root = dsu.find(i);
            auto& freq = compFreq[root];
            if (freq[target[i]] > 0) {
                --freq[target[i]];          // a match is possible
            } else {
                ++mismatches;               // unavoidable mismatch
            }
        }
        return mismatches;
    }
};
```

## Code Walkthrough

- **DSU construction** (`DSU dsu(n)`): `parent[i] = i` and `sz[i] = 1`.  
- **`unite`** merges two indices; union‑by‑size keeps the tree shallow, guaranteeing amortised $O(\alpha(n))$ per operation.  
- **`compFreq`**: a hash map keyed by the component root. The inner map stores how many times each value appears in `source` for that component.  
- **First loop (`i = 0 … n‑1`)** populates `compFreq`.  
- **Second loop** processes `target`. For the current index `i`, we look up the root component.  
  - If `freq[target[i]]` is positive, we consume one occurrence (the value can be moved to position `i`).  
  - Otherwise we increment `mismatches`, because no element in this component can satisfy `target[i]`.  
- The final `mismatches` count is the minimal possible Hamming distance.
