# 2770. Maximum Number of Jumps to Reach the Last Index

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 117 ms &nbsp;|&nbsp; **Memory:** 133.5 MB

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

The jump condition only depends on the **previous index** and the **current index**.  
Because every jump must move forward (`i < j`), the indices form a **directed acyclic graph** where an edge `i → j` exists iff `|nums[j]‑nums[i]| ≤ target`.  
The problem therefore reduces to finding the **longest path** from vertex 0 to vertex $n‑1$ in this DAG.  
Since the graph is already topologically ordered by the index, a simple DP that records the best reachable jump count for each index suffices.

## Approach

1. Create an array `dp` where `dp[i]` stores the maximum number of jumps needed to reach index `i`.  
   Initialise `dp[0] = 0` (no jump needed to stay at the start) and all other entries to a very negative value (unreachable sentinel).  
2. Iterate `i` from `1` to `n‑1`.  
   For each `i`, scan all previous indices `j < i`.  
   If `|nums[i] - nums[j]| ≤ target` **and** `dp[j]` is reachable, update  
   `dp[i] = max(dp[i], dp[j] + 1)`.  
3. After processing, `dp[n‑1]` holds the maximum jump count to the last index.  
   If it is still negative, return `-1`; otherwise return `dp[n‑1]`.

## Complexity Analysis

|                | Complexity | Reason                                                                      |
|----------------|------------|-----------------------------------------------------------------------------|
| **Time**       | $O(n^2)$   | Double loop over all pairs `(j,i)` with `j < i`, $n ≤ 1000$ makes it feasible |
| **Space**      | $O(n)$     | One DP array of length `n`                                                   |

## Key Takeaways

- **Longest path in a forward‑only graph**: When moves are only to larger indices, the graph is automatically topologically sorted, allowing a single forward DP pass.  
- **Unreachable sentinel**: Using a large negative constant (e.g., `-1e9`) cleanly distinguishes reachable states from impossible ones without extra boolean arrays.  
- **Quadratic DP is optimal for $n ≤ 1000$**: The $O(n^2)$ solution comfortably fits the constraints; for larger `n` one would need range‑query structures (segment tree / BIT) keyed by `nums` values.  
- **Absolute‑difference condition**: The edge existence test `|nums[i] - nums[j]| ≤ target` is constant‑time, so the DP transition remains simple and fast.

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
        vector<int> prevDp(n, INT_MIN);
        int res = -1;
        prevDp[0] = 0;
        for(int ind = 0;ind <= n - 2;ind++){
            vector<int> currDp(n, INT_MIN);
            for(int prev = 0;prev <= n - 1;prev++){
                int notTake = 0 + prevDp[prev];
                int take = -1e9;
                if(abs(nums[ind] - nums[prev]) <= target){
                    take = 1 + prevDp[ind];
                }
                currDp[prev] = max(take, notTake);
            }
            prevDp = currDp;
        }
        return max(res, prevDp[n-1]);
    }
};
```

## Professional Refactor

```cpp
// 2770. Maximum Number of Jumps to Reach the Last Index
// O(n^2) time, O(n) space
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        const int INF_NEG = -1e9;                 // sentinel for unreachable
        int n = nums.size();
        vector<int> dp(n, INF_NEG);
        dp[0] = 0;                                // start position

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (abs(nums[i] - nums[j]) <= target && dp[j] != INF_NEG) {
                    dp[i] = max(dp[i], dp[j] + 1);   // take jump j → i
                }
            }
        }
        return dp[n - 1] == INF_NEG ? -1 : dp[n - 1];
    }
};
```

## Code Walkthrough

- **Line 5‑6**: Define a large negative constant `INF_NEG` to represent an unreachable state.  
- **Line 9**: `dp[0] = 0` because we start at index 0 with zero jumps.  
- **Lines 11‑15**: For each target index `i`, examine all earlier indices `j`.  
  - The condition `abs(nums[i] - nums[j]) <= target` checks the jump feasibility.  
  - `dp[j] != INF_NEG` guarantees that `j` is reachable.  
  - `dp[i] = max(dp[i], dp[j] + 1)` records the best (maximum) jump count arriving at `i`.  
- **Line 18**: If `dp[n‑1]` stayed negative, the last index is unreachable → return `-1`; otherwise return the stored maximum.
