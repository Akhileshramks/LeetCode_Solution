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

The allowed swaps partition the indices into **disjoint connected components**.  
Inside one component we can reorder the elements of `source` arbitrarily because any permutation can be achieved by a sequence of pairwise swaps. Consequently, the only thing that matters for a component is **how many of each value it contains**, not their original positions.  
The minimal Hamming distance is therefore obtained by, for each component, matching as many `target` values as possible with the available `source` values. Unmatched target values contribute 1 to the distance.

## Approach

1. **Build components** – Use a Union‑Find (Disjoint Set Union) structure to union the two indices of every `allowedSwaps[i]`. After processing all swaps, `find(i)` returns the component identifier (root) of index `i`.
2. **Count source frequencies per component** – Iterate `i = 0 … n‑1`, obtain `root = find(i)`, and increment `cnt[root][source[i]]` in a hash map (`cnt` maps root → value → frequency).
3. **Match target values** – Iterate again over all indices:  
   * `root = find(i)`.  
   * If `cnt[root][target[i]] > 0`, a matching source element exists → decrement the count (the position can be fixed).  
   * Otherwise, no matching element is available in this component → increase the answer (`result++`).
4. Return `result`, the number of positions that cannot be matched.

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(n \,\alpha(n) + m \,\alpha(n)) = O(n+m)$ | Union‑Find operations are amortized $α(n)$; we traverse the arrays twice. |
| **Space**      | $O(n)$     | One parent/size array for DSU and a hash map storing at most $n$ value counts. |

## Key Takeaways

- **Swap graph → DSU**: Transform the arbitrary‑order swap constraint into connected components using Union‑Find; this reduces a seemingly combinatorial problem to independent subproblems.  
- **Component as a multiset**: Within a component the exact ordering is irrelevant; treat the `source` values as a multiset and match against `target` values greedily.  
- **Hash‑map frequency counters**: Maintaining a per‑component frequency map avoids sorting or expensive set operations while still providing $O(1)$ look‑ups for matches.  
- **Near‑linear performance**: Union‑by‑size + path compression guarantees almost linear time even for the maximum constraints ($n, m \le 10^5$).
