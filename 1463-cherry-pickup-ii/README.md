# 1463. Cherry Pickup II

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming, Matrix &nbsp;|&nbsp; **Solved:** April 23, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 64 ms &nbsp;|&nbsp; **Memory:** 22 MB

---

## Problem

You are given a `rows x cols` matrix `grid` representing a field of cherries where `grid[i][j]` represents the number of cherries that you can collect from the `(i, j)` cell.

You have two robots that can collect cherries for you:

	
- **Robot #1** is located at the **top-left corner** `(0, 0)`, and
	
- **Robot #2** is located at the **top-right corner** `(0, cols - 1)`.

Return _the maximum number of cherries collection using both robots by following the rules below_:

	
- From a cell `(i, j)`, robots can move to cell `(i + 1, j - 1)`, `(i + 1, j)`, or `(i + 1, j + 1)`.
	
- When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
	
- When both robots stay in the same cell, only one takes the cherries.
	
- Both robots cannot move outside of the grid at any moment.
	
- Both robots should reach the bottom row in `grid`.

 

**Example 1:**

![](https://assets.leetcode.com/uploads/2020/04/29/sample_1_1802.png)

> **Input:** grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
> **Output:** 24
> **Explanation:** Path of robot #1 and #2 are described in color green and blue respectively.
> Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
> Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
> Total of cherries: 12 + 12 = 24.

**Example 2:**

![](https://assets.leetcode.com/uploads/2020/04/23/sample_2_1802.png)

> **Input:** grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
> **Output:** 28
> **Explanation:** Path of robot #1 and #2 are described in color green and blue respectively.
> Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
> Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
> Total of cherries: 17 + 11 = 28.

## Constraints

- `rows == grid.length`
	
- `cols == grid[i].length`
	
- `2 <= rows, cols <= 70`
	
- `0 <= grid[i][j] <= 100`

## Hints

1. Use dynamic programming, define DP[i][j][k]: The maximum cherries that both robots can take  starting on the ith row, and column j and k of Robot 1 and 2 respectively.

---

## Intuition

The robots always move **synchronously** one row down, and each robot’s next column can only differ by at most 1.  
Therefore the whole future only depends on three variables: the current row `i` and the two column positions `j₁` and `j₂`.  
If we treat the pair `(j₁, j₂)` as a single state, the problem becomes a classic **dynamic programming** on a 3‑dimensional state space.  
The “Aha!” moment is realizing that we do **not** need to keep the whole path – just the best achievable total from any state `(i, j₁, j₂)` onward.

## Approach

1. **State definition**  
   `dp[i][j₁][j₂]` = maximum cherries collectable from row `i` to the bottom when robot 1 is at column `j₁` and robot 2 at column `j₂` in row `i`.

2. **Transition**  
   From `(i, j₁, j₂)` each robot can move to `j‑1`, `j`, or `j+1`.  
   Enumerate the 9 possible pairs `(δ₁, δ₂) ∈ {‑1,0,1}²` and pick the best next state:  

   \[
   dp[i][j₁][j₂] = \text{curr} + \max_{\delta₁,\delta₂}
   dp[i+1][j₁+\delta₁][j₂+\delta₂]
   \]

   where  

   \[
   \text{curr} = 
   \begin{cases}
   \text{grid}[i][j₁] & j₁ = j₂\\[4pt]
   \text{grid}[i][j₁] + \text{grid}[i][j₂] & j₁ \neq j₂
   \end{cases}
   \]

3. **Boundary handling**  
   Any transition that moves a robot outside `[0, cols‑1]` is invalid; treat its value as $-\infty$ so it never becomes the maximum.

4. **Base case**  
   For the last row `i = rows‑1` the value is simply `curr` because there are no further moves.

5. **Implementation choices**  
   *Top‑down* memoization works directly (as in the original code).  
   A *bottom‑up* version with a rolling 2‑D array (`dpPrev`, `dpCurr`) reduces memory from $O(rows·cols²)$ to $O(cols²)$.

## Complexity Analysis

|                | Complexity | Reason                                                                      |
|----------------|------------|-----------------------------------------------------------------------------|
| **Time**       | $O(rows \times cols^2 \times 9)$ = $O(rows \cdot cols^2)$ | For each of the $rows·cols^2$ states we examine 9 neighbour combinations. |
| **Space**      | $O(cols^2)$ (bottom‑up) or $O(rows \cdot cols^2)$ (top‑down) | Only the pair of columns per row is stored; rolling array cuts the first dimension. |

## Key Takeaways

* **Pair‑state DP** – When two agents move in lockstep, collapse their positions into a single composite state to obtain a tractable DP dimension.
* **Overlap handling** – Explicitly check `j₁ == j₂` and count the cell’s cherries only once; this subtle detail prevents double‑counting.
* **Invalid moves as $-\infty$** – Using a very negative sentinel eliminates extra `if` checks inside the inner maximisation loop.
* **Memory optimisation via rolling array** – Because the transition only depends on the next row, a 2‑D `cols × cols` table suffices, shrinking memory from ~70³ to ~70².

## My Original Solution

```cpp
class Solution {
public:
    int pickUp(vector<vector<int>>& grid, int i, int j1, int j2, int n,int m,vector<vector<vector<int>>>& dp){
        if(j1 < 0 || j2 < 0 || i < 0 || j1 >= m || j2 >= m || i >= n) return -1;
        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
        int nextStep = 0;
        int dy[3] = {-1,0,1};
        int currStep = j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        for(int dy1 : dy){
            for(int dy2 : dy){
                nextStep = max(nextStep, pickUp(grid, i+1, j1+dy1, j2+dy2, n, m, dp));
            }
        }
        return dp[i][j1][j2] = nextStep + currStep;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return pickUp(grid,0,0,m-1,n,m,dp);
    }
};
```

## Professional Refactor

```cpp
// 1463. Cherry Pickup II – bottom‑up DP with rolling arrays
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        const int R = grid.size();
        const int C = grid[0].size();
        const int NEG = -1e9;               // sentinel for impossible states

        // dpPrev[j1][j2] holds values for row i+1, dpCurr for row i
        vector<vector<int>> dpPrev(C, vector<int>(C, NEG));
        vector<vector<int>> dpCurr(C, vector<int>(C, NEG));

        // Initialise base row (bottom row)
        for (int j1 = 0; j1 < C; ++j1) {
            for (int j2 = 0; j2 < C; ++j2) {
                dpPrev[j1][j2] = (j1 == j2) ? grid[R-1][j1]
                                            : grid[R-1][j1] + grid[R-1][j2];
            }
        }

        // Process rows from bottom‑1 up to the top
        for (int i = R - 2; i >= 0; --i) {
            for (int j1 = 0; j1 < C; ++j1) {
                for (int j2 = 0; j2 < C; ++j2) {
                    int best = NEG;
                    // try all 3×3 moves
                    for (int d1 = -1; d1 <= 1; ++d1) {
                        int nj1 = j1 + d1;
                        if (nj1 < 0 || nj1 >= C) continue;
                        for (int d2 = -1; d2 <= 1; ++d2) {
                            int nj2 = j2 + d2;
                            if (nj2 < 0 || nj2 >= C) continue;
                            best = max(best, dpPrev[nj1][nj2]);
                        }
                    }
                    int cur = (j1 == j2) ? grid[i][j1]
                                         : grid[i][j1] + grid[i][j2];
                    dpCurr[j1][j2] = cur + best;
                }
            }
            dpPrev.swap(dpCurr);   // move up one row
        }

        // start positions: (0,0) and (0,C‑1)
        return dpPrev[0][C-1];
    }
};
```

## Code Walkthrough

* **State tables (`dpPrev`, `dpCurr`)** – each entry `dpPrev[j₁][j₂]` stores the optimal total from the *next* row downwards. Using two 2‑D arrays implements the rolling‑row optimisation.
* **Base initialization** – For the bottom row we can directly compute the collected cherries because no further moves exist.
* **Transition loops** – The double `for (d1)` / `for (d2)` enumerates the 9 admissible moves. Out‑of‑bounds columns are skipped, guaranteeing we never read invalid indices.
* **Overlap check** – `cur` adds `grid[i][j₁]` once when `j₁ == j₂`; otherwise both cells are summed.
* **Row iteration** – We iterate from the second‑last row upward (`i = R‑2 … 0`). After finishing a row we `swap` the tables so the just‑computed values become the “next row” for the following iteration.
* **Result** – The answer corresponds to the starting configuration `(0, 0)` and `(0, C‑1)`, i.e. `dpPrev[0][C‑1]` after the final swap.
