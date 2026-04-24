# 279. Perfect Squares

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming, Breadth-First Search &nbsp;|&nbsp; **Solved:** April 24, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 175 ms &nbsp;|&nbsp; **Memory:** 160.5 MB

---

## Problem

Given an integer `n`, return _the least number of perfect square numbers that sum to_ `n`.

A **perfect square** is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, `1`, `4`, `9`, and `16` are perfect squares while `3` and `11` are not.

 

**Example 1:**

> **Input:** n = 12
> **Output:** 3
> **Explanation:** 12 = 4 + 4 + 4.

**Example 2:**

> **Input:** n = 13
> **Output:** 2
> **Explanation:** 13 = 4 + 9.

## Constraints

- `1 <= n <= 104`

## Hints

_No hints provided._

---

## Intuition

The problem is identical to the **unbounded coin change** where the coin denominations are all perfect squares ≤ $n$.  
We need the *shortest* combination, i.e. the minimum number of coins to reach the target sum.  
Because each edge (adding a square) has equal weight 1, the search space forms an **unweighted graph** whose nodes are the intermediate sums $0\ldots n$.  
The first time we reach $n$ in a **Breadth‑First Search (BFS)** we have used the fewest squares.  
Thus the “aha” insight is: *treat the numbers as graph levels and use BFS (or a 1‑D DP) to obtain the shortest path*.

## Approach

1. **Generate squares**  
   ```cpp
   vector<int> squares;
   for (int i = 1; i*i <= n; ++i) squares.push_back(i*i);
   ```
2. **BFS**  
   * Initialise a queue with the start node `0` and a distance array `dist` where `dist[0]=0`.  
   * While the queue is not empty, pop `cur`. For each `sq` in `squares`:
     * Let `next = cur + sq`. If `next > n` break (squares are sorted).  
     * If `dist[next]` is still `-1`, set `dist[next] = dist[cur] + 1` and push `next`.  
     * As soon as `next == n` we can return `dist[next]` – BFS guarantees optimality.
3. **Return** the distance for `n`.

*Alternative 1‑D DP* (same complexity, often faster in practice):  
`dp[0]=0; dp[i]=\min_{sq\le i}(dp[i-sq]+1)` for `i=1..n`.

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(n\sqrt{n})$ | There are $\sqrt{n}$ squares; each node $0\ldots n$ is processed at most once. |
| **Space**      | $O(n)$        | Distance/visited array of size $n+1$ and a queue holding at most $n$ nodes. |

## Key Takeaways

- **Coin‑change equivalence**: Perfect‑square decomposition is a classic unbounded knapsack with unit weight, enabling DP/BFS solutions.  
- **BFS yields optimal count** because every edge (adding a square) has equal cost; the first visitation of a sum is its minimal count.  
- **Upper bound of 4** (Lagrange’s Four‑Square Theorem) guarantees the answer never exceeds $4$, which can be used for early termination in more advanced variants.  
- **Generating squares via $i^2$** is $O(\sqrt{n})$ and avoids the odd‑increment trick used in the original code, improving readability and cache friendliness.

## My Original Solution

```cpp
class Solution {
public:
    int countMinElements(vector<int>& nums, int ind, int target,vector<vector<int>>& dp){
        if(target == 0) return 0;
        if(ind == 0){
            return target % nums[ind] == 0 ?  target / nums[ind] : INT_MAX;
        }
        if(dp[ind][target] != -1) return dp[ind][target];
        int notTake = countMinElements(nums, ind - 1, target, dp);
        int take = INT_MAX;
        if(nums[ind] <= target){
            take = min(take, countMinElements(nums,ind,target - nums[ind], dp));
        }
        if(take != INT_MAX) take += 1;
        return dp[ind][target] = min(take, notTake);
    }
    int numSquares(int n) {
        vector<int> nums;
        int currSum = 3;
        int perfectSquare = 1;
        for(int i = 1; perfectSquare <= n;currSum += 2){
            nums.push_back(perfectSquare);
            perfectSquare += currSum;
        }
        int m = nums.size();
        vector<vector<int>> dp(m, vector<int>(n+1, -1));
        return countMinElements(nums, m-1, n, dp);

    }
};
```

## Professional Refactor

```cpp
// bfs_solution.cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        // 1️⃣ generate all perfect squares ≤ n
        vector<int> squares;
        for (int i = 1; i * i <= n; ++i) squares.push_back(i * i);

        // 2️⃣ BFS over sums 0…n
        vector<int> dist(n + 1, -1);          // -1 ⇔ unvisited
        queue<int> q;
        q.push(0);
        dist[0] = 0;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int sq : squares) {
                int nxt = cur + sq;
                if (nxt > n) break;           // squares are sorted ascending
                if (dist[nxt] == -1) {        // first visit → minimal count
                    dist[nxt] = dist[cur] + 1;
                    if (nxt == n) return dist[nxt];
                    q.push(nxt);
                }
            }
        }
        return dist[n]; // should never reach here because Lagrange guarantees ≤4
    }
};
```

## Code Walkthrough

- **Square generation** (`for (int i = 1; i * i <= n; ++i)`) replaces the odd‑increment trick, yielding a clear $O(\sqrt{n})$ list.
- **`dist` array** serves both as a visited flag and as the DP state `dp[i] = minimal squares to reach i`.  
- **BFS loop**: each dequeue expands to all possible next sums by adding each square. Because we break when `nxt > n`, we never generate out‑of‑range states.
- **Early return** (`if (nxt == n)`) exploits BFS’s guarantee that the first time we hit `n` we have used the fewest squares, avoiding the need to process the entire graph.
