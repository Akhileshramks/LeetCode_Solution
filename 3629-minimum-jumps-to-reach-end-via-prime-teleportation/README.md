# 3629. Minimum Jumps to Reach End via Prime Teleportation

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Hash Table, Math, Breadth-First Search, Number Theory &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 351 ms &nbsp;|&nbsp; **Memory:** 364.9 MB

---

## Problem

You are given an integer array `nums` of length `n`.

You start at index 0, and your goal is to reach index `n - 1`.

From any index `i`, you may perform one of the following operations:

	
- **Adjacent Step**: Jump to index `i + 1` or `i - 1`, if the index is within bounds.
	
- **Prime Teleportation**: If `nums[i]` is a prime number `p`, you may instantly jump to any index `j != i` such that `nums[j] % p == 0`.

Return the **minimum** number of jumps required to reach index `n - 1`.

 

**Example 1:**

**Input:** nums = [1,2,4,6]

**Output:** 2

**Explanation:**

One optimal sequence of jumps is:

	
- Start at index `i = 0`. Take an adjacent step to index 1.
	
- At index `i = 1`, `nums[1] = 2` is a prime number. Therefore, we teleport to index `i = 3` as `nums[3] = 6` is divisible by 2.

Thus, the answer is 2.

**Example 2:**

**Input:** nums = [2,3,4,7,9]

**Output:** 2

**Explanation:**

One optimal sequence of jumps is:

	
- Start at index `i = 0`. Take an adjacent step to index `i = 1`.
	
- At index `i = 1`, `nums[1] = 3` is a prime number. Therefore, we teleport to index `i = 4` since `nums[4] = 9` is divisible by 3.

Thus, the answer is 2.

**Example 3:**

**Input:** nums = [4,6,5,8]

**Output:** 3

**Explanation:**

	
- Since no teleportation is possible, we move through `0 &rarr; 1 &rarr; 2 &rarr; 3`. Thus, the answer is 3.

## Constraints

- `1 <= n == nums.length <= 105`
	
- `1 <= nums[i] <= 106`

## Hints

1. Use a breadth-first search.
2. Precompute prime factors of each `nums[i]` via a sieve, and build a bucket `bucket[p]` mapping each prime `p` to all indices `j` with `nums[j] % p == 0`.
3. During the BFS, when at index `i`, enqueue its adjacent steps (`i+1` and `i-1`) and all indices in `bucket[p]` for each prime `p` dividing `nums[i]`, then clear `bucket[p]` so each prime's bucket is visited only once.

---

## Intuition

The graph is implicit: each index connects to its neighbours and to **all** other indices whose values share a prime divisor with the current value.  
The “aha” is to treat each *prime* as a hub – once we teleport through a prime, we never need to consider that hub again because every reachable node via that prime has already been visited at the minimal distance. By clearing the hub’s adjacency list after first use we avoid the quadratic blow‑up that a naïve “connect every pair sharing a prime” would cause.

## Approach

1. **Pre‑compute prime factors** for every number up to $\max(\text{nums})$ using a linear sieve (or classic SPF sieve).  
   `factors[x]` stores the *distinct* prime divisors of $x$.

2. **Build prime‑to‑indices map**: for each index $i$, insert $i$ into `primeBuckets[p]` for every $p \in \text{factors}[ \text{nums}[i] ]$.

3. **Breadth‑First Search** from index 0:  
   - Pop the current index $u$.  
   - Enqueue $u-1$ and $u+1$ if they are inside bounds and unvisited.  
   - For each prime $p$ in `factors[nums[u]]`:
     * Iterate over all indices $v$ stored in `primeBuckets[p]`.  
     * If $v \neq u$ and unvisited, enqueue $v$.  
   - **Crucial step**: after processing prime $p$, clear `primeBuckets[p]`. This guarantees each prime hub is traversed at most once, turning potentially $O(n^2)$ edges into $O(n \cdot \text{avg\_factors})$.

4. The BFS level counter is the minimum number of jumps; return it when index $n-1$ is dequeued.

## Complexity Analysis

|                | Complexity | Reason                                                                                         |
|----------------|------------|------------------------------------------------------------------------------------------------|
| **Time**       | $O\bigl(N \cdot \log V_{\max}\bigr)$ | Sieve: $O(V_{\max}\log\log V_{\max})$, building buckets: $\sum_i |\text{factors}[nums_i]|$, BFS: each index visited once + each prime hub cleared once. |
| **Space**      | $O\bigl(N + V_{\max}\bigr)$       | `factors` array up to $V_{\max}=10^6$, `primeBuckets` holding at most $N$ total indices, plus BFS queue & visited array. |

Here $N = \text{nums.size()}$ and $V_{\max} = \max(\text{nums})$.

## Key Takeaways

- **Prime hubs**: collapsing all teleport edges that share a prime into a single “hub” node reduces the graph from dense to linear‑size.
- **One‑time hub expansion**: clearing a prime’s bucket after its first expansion prevents repeated scans and guarantees linear total work.
- **Pre‑computing distinct prime factors** (instead of full factorization per query) is essential to meet the $10^5$‑element constraint with values up to $10^6$.
- BFS on this transformed graph directly yields the optimal number of jumps because every edge (adjacent or teleport) has unit cost.
