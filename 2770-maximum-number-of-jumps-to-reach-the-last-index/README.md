# 2770. Maximum Number of Jumps to Reach the Last Index

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 95 ms &nbsp;|&nbsp; **Memory:** 136.6 MB

---

## Problem

You are given a **0-indexed** array `nums` of `n` integers and an integer `target`.

You are initially positioned at index `0`. In one step, you can jump from index `i` to any index `j` such that:

	
- `0 <= i < j < n`
	
- `-target <= nums[j] - nums[i] <= target`

Return _the **maximum number of jumps** you can make to reach index_ `n - 1`.

If there is no way to reach index `n - 1`, return `-1`.

 

**Example 1:**

> **Input:** nums = [1,3,6,4,1,2], target = 2
> **Output:** 3
> **Explanation:** To go from index 0 to index n - 1 with the maximum number of jumps, you can perform the following jumping sequence:
> - Jump from index 0 to index 1. 
> - Jump from index 1 to index 3.
> - Jump from index 3 to index 5.
> It can be proven that there is no other jumping sequence that goes from 0 to n - 1 with more than 3 jumps. Hence, the answer is 3.

**Example 2:**

> **Input:** nums = [1,3,6,4,1,2], target = 3
> **Output:** 5
> **Explanation:** To go from index 0 to index n - 1 with the maximum number of jumps, you can perform the following jumping sequence:
> - Jump from index 0 to index 1.
> - Jump from index 1 to index 2.
> - Jump from index 2 to index 3.
> - Jump from index 3 to index 4.
> - Jump from index 4 to index 5.
> It can be proven that there is no other jumping sequence that goes from 0 to n - 1 with more than 5 jumps. Hence, the answer is 5.

**Example 3:**

> **Input:** nums = [1,3,6,4,1,2], target = 0
> **Output:** -1
> **Explanation:** It can be proven that there is no jumping sequence that goes from 0 to n - 1. Hence, the answer is -1.

## Constraints

- `2 <= nums.length == n <= 1000`
	
- `-109 <= nums[i] <= 109`
	
- `0 <= target <= 2 * 109`

## Hints

1. Use a dynamic programming approach.
2. Define a dynamic programming array dp of size n, where dp[i] represents the maximum number of jumps from index 0 to index i.
3. For each j iterate over all i < j. Set dp[j] = max(dp[j], dp[i] + 1) if -target <= nums[j] - nums[i] <= target.

---

## Intuition

The jump condition creates a **directed acyclic graph (DAG)**: every valid jump goes from a smaller index $i$ to a larger index $j$, so cycles are impossible.  
Finding the maximum number of jumps from index 0 to index $n\!-\!1$ is therefore exactly the problem of finding the **longest path** in this DAG.  
Because $n\le 1000$, we can afford the $O(n^2)$ edge enumeration and apply a simple DP that propagates the best length forward.

## Approach

1. **Initialize DP** – `dp[i]` stores the maximum number of jumps needed to reach index $i$ from index 0.  
   Set `dp[0]=0` and all other entries to a large negative sentinel (unreachable).

2. **Enumerate edges** – For each source index `i` (from 0 to $n‑2`), iterate all possible destinations `j>i`.  
   If `|nums[j]‑nums[i]| ≤ target`, the jump `i→j` is allowed.

3. **Relax DP** – When an allowed jump is found, update  
   `dp[j] = max(dp[j], dp[i] + 1)`.  
   This propagates the longest‑so‑far path to `j`.

4. **Result** – After processing all pairs, `dp[n‑1]` holds the maximum jumps to the last index.  
   If it is still the negative sentinel, return `-1`; otherwise return `dp[n‑1]`.

## Complexity Analysis

|                | Complexity | Reason |
|----------------|------------|--------|
| **Time**       | $O(n^2)$   | Two nested loops over all index pairs $(i,j)$ with $i<j$. |
| **Space**      | $O(n)$     | One DP array of length $n$ (the recursion stack in the original solution is eliminated). |

## Key Takeaways

- **Longest path in a DAG** can be solved by a straightforward DP when the graph is dense but $n$ is modest ($\le 10^3$).  
- Converting the jump rule into an edge predicate (`|nums[j]‑nums[i]| ≤ target`) yields a clean, index‑ordered graph, guaranteeing acyclicity.  
- Using a **negative sentinel** (e.g., $-10^9$) distinguishes unreachable states without extra boolean arrays.  
- A **forward DP** (propagating from start to end) is usually clearer and less error‑prone than a backward recursive formulation with two parameters.

## My Original Solution

```cpp
class Solution {
public:
    int findMaxJump(vector<int>& nums, int ind, int prev, vector<vector<int>>& dp, int target){
        if(ind < 0) return prev == 0 ? 0 : -1e9;
        if(dp[ind][prev] != -1) return dp[ind][prev];
        int notTake = 0 + findMaxJump(nums, ind - 1, prev, dp, target);
        int take = -1e9;
        if(abs(nums[ind] - nums[prev]) <= target){
            take = 1 + findMaxJump(nums, ind - 1, ind, dp, target);
        }
        return dp[ind][prev] = max(take, notTake);
    }
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        int res = findMaxJump(nums, n - 2, n - 1, dp, target);
        return res <  0 ? -1 : res;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        const int NEG_INF = -1e9;               // sentinel for unreachable
        int n = nums.size();
        vector<int> dp(n, NEG_INF);
        dp[0] = 0;                               // start at index 0

        // forward DP over all ordered pairs (i, j)
        for (int i = 0; i < n; ++i) {
            if (dp[i] == NEG_INF) continue;     // cannot reach i, skip
            for (int j = i + 1; j < n; ++j) {
                if (abs(nums[j] - nums[i]) <= target) {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }

        return dp[n - 1] == NEG_INF ? -1 : dp[n - 1];
    }
};
```

## Code Walkthrough

- **`dp` initialization** – `dp[0]=0` because we start there with zero jumps; all other entries are set to `NEG_INF` to mark them unreachable.
- **Outer loop (`i`)** – Processes indices in increasing order, guaranteeing that when we relax edges from `i`, `dp[i]` already holds the longest path to `i`.
- **Inner loop (`j`)** – Checks the jump feasibility `|nums[j]‑nums[i]| ≤ target`. If true, we can extend any optimal path to `i` by one more jump, hence `dp[j] = max(dp[j], dp[i] + 1)`.
- **Early skip** – `if (dp[i] == NEG_INF) continue;` avoids unnecessary work for indices that cannot be reached.
- **Result extraction** – After all relaxations, `dp[n‑1]` contains the answer; if it stayed `NEG_INF`, no valid sequence exists, so we return `-1`.
