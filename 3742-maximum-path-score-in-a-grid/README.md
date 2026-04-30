# 3742. Maximum Path Score in a Grid

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming, Matrix &nbsp;|&nbsp; **Solved:** April 30, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 1309 ms &nbsp;|&nbsp; **Memory:** 499.5 MB

---

## Problem

You are given an `m x n` grid where each cell contains one of the values 0, 1, or 2. You are also given an integer `k`.

You start from the top-left corner `(0, 0)` and want to reach the bottom-right corner `(m - 1, n - 1)` by moving only **right** or **down**.

Each cell contributes a specific score and incurs an associated cost, according to their cell values:

	
- 0: adds 0 to your score and costs 0.
	
- 1: adds 1 to your score and costs 1.
	
- 2: adds 2 to your score and costs 1. ​​​​​​​

Return the **maximum** score achievable without exceeding a total cost of `k`, or -1 if no valid path exists.

**Note:** If you reach the last cell but the total cost exceeds `k`, the path is invalid.

 

**Example 1:**

**Input:** grid = [[0, 1],[2, 0]], k = 1

**Output:** 2

**Explanation:**​​​​​​​

The optimal path is:

	
		
			Cell
			grid[i][j]
			Score
			Total

			Score
			Cost
			Total

			Cost
		
	
	
		
			(0, 0)
			0
			0
			0
			0
			0
		
		
			(1, 0)
			2
			2
			2
			1
			1
		
		
			(1, 1)
			0
			0
			2
			0
			1
		
	

Thus, the maximum possible score is 2.

**Example 2:**

**Input:** grid = [[0, 1],[1, 2]], k = 1

**Output:** -1

**Explanation:**

There is no path that reaches cell `(1, 1)`​​​​​​​ without exceeding cost k. Thus, the answer is -1.

## Constraints

- `1 <= m, n <= 200`
	
- `0 <= k <= 103​​​​​​​`
	
- `​​​​​​​grid[0][0] == 0`
	
- `0 <= grid[i][j] <= 2`

## Hints

1. Use dynamic programming.
2. Let `dp[i][j][c]` = max score at cell `(i,j)` with total cost exactly `c` (0 <= `c` <= `k`).
3. Update `dp[i][j][c]` from `(i-1,j)` and `(i,j-1)` using `cost = (grid[i][j] == 0 ? 0 : 1)` and `score = grid[i][j]`.
4. Answer = `max(dp[m-1][n-1][c])` for `c=0..k`, or `-1` if none.

---

## Intuition

The grid can be traversed only right or down, so every path is a monotone walk from the top‑left to the bottom‑right.  
Each cell contributes a **fixed cost** (0 for value 0, 1 otherwise) and a **fixed score** (0, 1, 2 respectively).  
Thus the problem becomes: *choose a monotone path whose total cost ≤ $k$ while maximizing the sum of scores*.  

This is exactly a **knapsack‑style DP** on a 2‑D lattice: for every cell we must remember **how much budget we have already spent** (or equivalently, how much budget remains) because the optimal continuation depends on the remaining allowance. The “aha” moment is to treat the cost budget as an extra dimension of the DP state instead of trying to prune paths greedily.

## Approach

1. **Pre‑compute cell contribution**  
   ```cpp
   // cost, score
   (0) → (0,0) , (1) → (1,1) , (2) → (1,2)
   ```
2. **DP definition**  
   $dp[i][j][c]$ = maximum score achievable **from cell $(i,j)$ to the destination** when we have already spent exactly $c$ cost on the prefix **including** $(i,j)$.  
   If no valid continuation exists, store $-1$.
3. **Base case (bottom‑right)**  
   For every feasible $c$ (i.e. $c + \text{cost}_{\text{end}} \le k$) set  
   $dp[m-1][n-1][c] = \text{score}_{\text{end}}$.
4. **Transition (bottom‑up)**  
   Iterate cells in reverse order (from bottom‑right to top‑left).  
   For each $c$:
   *If $c + \text{cost}_{i,j} > k$ → impossible, continue.*  
   Otherwise look at the two reachable successors:
   ```text
   down  → dp[i+1][j][c + cost(i,j)]
   right → dp[i][j+1][c + cost(i,j)]
   ```
   Take the larger of the two (ignoring $-1$), add $\text{score}_{i,j}$, and store it as $dp[i][j][c]$.
5. **Answer**  
   The start cell has not spent any cost yet, so the answer is  
   $\displaystyle \max_{0\le c\le k} dp[0][0][c]$.  
   If all entries are $-1$, return $-1$.

## Complexity Analysis

|               | Complexity | Reason |
|---|---|---|
| **Time**  | $O(m \cdot n \cdot k)$ | Every cell $(i,j)$ processes all $k\!+\!1$ possible spent‑cost values and checks two neighbours. |
| **Space** | $O(m \cdot n \cdot k)$ | Full 3‑D DP table; can be reduced to $O(n \cdot k)$ with row‑wise rolling, but not required for the given limits. |

## Key Takeaways

* **Cost‑augmented DP** – when a path constraint (budget, length, etc.) is additive, embed it as an extra DP dimension rather than trying to prune greedily.  
* **Bottom‑up over monotone grids** – processing cells in reverse order guarantees that both successors are already computed, eliminating recursion overhead.  
* **Sentinel handling** – using $-1$ (or $-\infty$) to denote “impossible” lets the transition stay simple: `max(valid_successors)`.  
* **Pre‑mapping cell values** – converting the raw grid values into `(cost, score)` pairs once avoids repeated `if`/`switch` inside the tight DP loops.

## My Original Solution

```cpp
class Solution {
public:
    pair<int,int> findCostScore(int i){
        if(i == 0) return {0, 0};
        else if(i == 1) return {1,1};
        else return {1,2};
    }
    int findMaxPath(vector<vector<int>>& grid, int i, int j, int cost, int k, int n, int m, vector<vector<vector<int>>>& dp){
            if(i == n - 1 && j == m - 1){
                pair<int,int> new_cs = findCostScore(grid[i][j]);
                if(cost + new_cs.first <= k) return new_cs.second;
                else return -1;
            }
            pair<int,int> curr_cs = findCostScore(grid[i][j]);
            if(cost + curr_cs.first > k) return -1;
            if(dp[i][j][cost] != -2) return dp[i][j][cost];
            int next_score = -1;
            vector<vector<int>> nextState = {{1, 0}, {0, 1}};
            for(int r = 0;r < 2;r++){
                int next_i = i + nextState[r][0], next_j = j + nextState[r][1];
                if(next_i >= 0 && next_i < n && next_j >= 0 && next_j < m){
                    next_score = max(next_score, findMaxPath(grid, next_i, next_j, cost + curr_cs.first, k, n, m, dp));
                }
            }
            return dp[i][j][cost] = next_score != -1 ? next_score + curr_cs.second :  -1;
    }
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        int ans = -1;

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k+1, -1)));

        for(int cost = 0; cost <= k; cost++){
            auto [c, s] = findCostScore(grid[n-1][m-1]);
            if(cost + c <= k) dp[n-1][m-1][cost] = s;
        }

        for(int i = n - 1;i >= 0;i--){
            for(int j = m - 1;j >= 0;j--){
                if(i == n - 1 && j == m - 1) continue;
                for(int cost = 0;cost <= k;cost++){
                    pair<int,int> curr_cs = findCostScore(grid[i][j]);
                    if(cost + curr_cs.first > k) continue;
                    int next_score = -1;
                    if(i + 1 < n && dp[i + 1][j][cost + curr_cs.first] != -1) next_score = max(next_score, dp[i + 1][j][cost + curr_cs.first]);
                    if(j + 1 < m && dp[i][j + 1][cost + curr_cs.first] != -1) next_score = max(next_score, dp[i][j + 1][cost + curr_cs.first]);
                    dp[i][j][cost] = next_score != -1 ? next_score + curr_cs.second :  -1;
                }
            }
        }
        for(int c = 0;c <= k; c++) ans = max(ans, dp[0][0][c]);
        return ans;
    }
};
```

## Professional Refactor

```cpp
class Solution {
    struct CellInfo {
        int cost;   // 0 for value 0, otherwise 1
        int score;  // 0, 1, or 2
    };

    // Translate raw cell value to (cost, score)
    static CellInfo decode(int v) {
        if (v == 0) return {0, 0};
        if (v == 1) return {1, 1};
        return {1, 2};               // v == 2
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int K) {
        const int m = grid.size();
        const int n = grid[0].size();

        // dp[i][j][c] = best score from (i,j) to end when we have already spent c cost
        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(K + 1, -1)));

        // ---- base case: bottom‑right cell ----
        CellInfo last = decode(grid[m - 1][n - 1]);
        for (int spent = 0; spent <= K; ++spent) {
            if (spent + last.cost <= K)
                dp[m - 1][n - 1][spent] = last.score;
        }

        // ---- fill table bottom‑up ----
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == m - 1 && j == n - 1) continue;   // already handled
                CellInfo cur = decode(grid[i][j]);

                for (int spent = 0; spent <= K; ++spent) {
                    if (spent + cur.cost > K) continue;   // exceeds budget

                    int best = -1;
                    // move down
                    if (i + 1 < m && dp[i + 1][j][spent + cur.cost] != -1)
                        best = max(best, dp[i + 1][j][spent + cur.cost]);
                    // move right
                    if (j + 1 < n && dp[i][j + 1][spent + cur.cost] != -1)
                        best = max(best, dp[i][j + 1][spent + cur.cost]);

                    if (best != -1) dp[i][j][spent] = best + cur.score;
                }
            }
        }

        // ---- answer: any feasible spent amount at the start ----
        int ans = -1;
        for (int spent = 0; spent <= K; ++spent)
            ans = max(ans, dp[0][0][spent]);
        return ans;
    }
};
```

## Code Walkthrough

*`decode`* – converts the three possible cell values into a pair `(cost, score)`. This isolates the mapping logic and avoids repeated `if` statements inside the DP loops.

*DP table allocation* – a 3‑D vector `dp[m][n][K+1]` initialized to `-1`. `-1` works as the “impossible” sentinel because scores are non‑negative.

*Base case* – for the destination cell we can finish the path with any already‑spent cost `spent` as long as `spent + cost_dest ≤ K`. The stored value is simply `score_dest`.

*Main loops* – iterate rows and columns in reverse order so that `dp[i+1][j][*]` (down) and `dp[i][j+1][*]` (right) are already computed.  
For each `(i,j,spent)` we first reject states that would exceed the budget (`spent + cur.cost > K`).  
Otherwise we look at the two possible moves, pick the larger reachable score (`best`), and add the current cell’s score. If neither move is feasible, the entry stays `-1`.

*Final aggregation* – the start cell has spent `0` cost initially, but any amount `spent` up to `K` could have been accumulated by the time we reach `(0,0)` in the DP definition. Hence we take the maximum over all `dp[0][0][spent]`. If none are reachable, `ans` remains `-1`.
