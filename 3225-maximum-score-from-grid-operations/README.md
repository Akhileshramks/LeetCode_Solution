# 3225. Maximum Score From Grid Operations

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming, Matrix, Prefix Sum &nbsp;|&nbsp; **Solved:** April 30, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 86 ms &nbsp;|&nbsp; **Memory:** 44 MB

---

## Problem

You are given a 2D matrix `grid` of size `n x n`. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices `(i, j)`, and color black all the cells of the `jth` column starting from the top row down to the `ith` row.

The grid score is the sum of all `grid[i][j]` such that cell `(i, j)` is white and it has a horizontally adjacent black cell.

Return the **maximum** score that can be achieved after some number of operations.

 

**Example 1:**

**Input:** grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]

**Output:** 11

**Explanation:**

![](https://assets.leetcode.com/uploads/2024/05/11/one.png)

In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is `grid[3][0] + grid[1][2] + grid[3][3]` which is equal to 11.

**Example 2:**

**Input:** grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]

**Output:** 94

**Explanation:**

![](https://assets.leetcode.com/uploads/2024/05/11/two-1.png)

We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is `grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4]` which is equal to 94.

## Constraints

- `1 <= n == grid.length <= 100`
	
- `n == grid[i].length`
	
- `0 <= grid[i][j] <= 109`

## Hints

1. Use dynamic programming.
2. Solve the problem in O(N^4) using a 3-states dp.
3. Let `dp[i][lastHeight][beforeLastHeight]` denote the maximum score if the grid was limited to column `i`, and the height of column `i - 1` is `lastHeight` and the height of column `i - 2` is `beforeLastHeight`.
4. The third state, `beforeLastHeight`, is used to determine which values of column `i - 1` will be added to the score.  We can replace this state with another state that only takes two values 0 or 1.
5. Let `dp[i][lastHeight][isBigger]` denote the maximum score if the grid was limited to column `i`, and where the height of column `i - 1` is `lastHeight`. Additionally, if `isBigger == 1`, the number of black cells in column `i` is assumed to be larger than the number of black cells in column `i - 2`, and vice versa. Note that if our assumption is wrong, it would lead to a suboptimal score and, therefore, it would not be considered as the final answer.

---

## Intuition  

The only way a white cell can earn points is if **its left neighbour is black**.  
If we look at each column independently, the operation always paints a *prefix* of that column black.  
Therefore each column can be described by a single integer `h` – the height of the black prefix (rows `0 … h‑1`).  

For two consecutive columns with heights `p` (previous) and `h` (current):

* rows `i < p` have a black cell on the left,
* rows `i ≥ h` stay white in the current column.

Hence the white cells that gain points are exactly the rows in the interval  

\[
[h,\;p)\quad\text{(only if }h\le p\text{)} .
\]

The contribution of column `j` is the sum of `grid[i][j]` over that interval, which can be obtained in O(1) with a column‑wise prefix sum.  
Thus the problem reduces to a dynamic program over columns where the state is the current height `h`. The “aha” is recognizing this height‑interval formulation and that the transition only needs the comparison `h ≤ p` versus `h > p`.

---

## Approach  

1. **Column prefix sums**  
   `pref[j][k] = Σ_{i=0}^{k-1} grid[i][j]` for every column `j`.  
   Allows `sum_{i=l}^{r-1} grid[i][j] = pref[j][r] – pref[j][l]` in O(1).

2. **DP definition**  
   `dpPrev[h]` – maximum score after processing columns `0 … j‑1` with height `h` for column `j‑1`.  
   Initialise `dpPrev[h] = 0` for all `h` (no score before the first column).

3. **Transition for column `j` (j ≥ 1)**  

   For every possible current height `h (0…n)` and every previous height `p (0…n)`  

   *If `h ≤ p`* (the black region shrinks or stays):  
   \[
   gain = pref[j-1][p] - pref[j-1][h]
   \]
   (rows `h … p‑1` become white with a black left neighbour).  

   *If `h > p`* (the black region expands):  
   no white cell has a black left neighbour, so `gain = 0`.

   Update  
   \[
   dpCurr[h] = \max(dpCurr[h],\; dpPrev[p] + gain).
   \]

4. After processing column `j`, replace `dpPrev ← dpCurr` and continue.

5. The answer is `max_h dpPrev[h]` after the last column.

The original code separates the two cases into `prevPick` / `prevSkip`, but the core idea is the same transition described above.

---

## Complexity Analysis  

|               | Complexity | Reason |
|---------------|------------|--------|
| **Time**      | $O(n^{3})$ | For each of the $n-1$ column transitions we iterate over all `h` and `p` (both $0…n$). |
| **Space**     | $O(n)$     | Two 1‑D DP arrays of size $n+1$ and the prefix matrix $O(n^{2})$ (the matrix itself). |

---

## Key Takeaways  

* **Height‑interval reduction** – turning a 2‑D painting operation into a 1‑D “cut height” DP reveals the hidden structure.  
* **Prefix sums per column** turn any interval sum into O(1), enabling the DP transition to stay simple.  
* **Two‑case transition** (`h ≤ p` vs. `h > p`) is the only source of score; recognizing that expanding the black prefix never adds points avoids unnecessary calculations.  
* Even with $n=100$, an $O(n^{3})$ DP is fast enough, but the formulation scales well to larger limits if needed (e.g., by monotone queue optimisation).

---

## My Original Solution

```cpp
class Solution {
 public:
  long long maximumScore(vector<vector<int>>& grid) {
    int n = grid.size();

    vector<vector<long long>> prefix(n, vector<long long>(n + 1, 0));
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < n; i++) {
        prefix[j][i + 1] = prefix[j][i] + grid[i][j];
      }
    }

    vector<long long> prevPick(n + 1, 0), prevSkip(n + 1, 0);

    for (int j = 1; j < n; j++) {
      vector<long long> currPick(n + 1, 0), currSkip(n + 1, 0);

      for (int curr = 0; curr <= n; curr++) {
        for (int prev = 0; prev <= n; prev++) {

          if (curr > prev) {
            long long score = prefix[j - 1][curr] - prefix[j - 1][prev];

            currPick[curr] = max(currPick[curr], prevSkip[prev] + score);
            currSkip[curr] = max(currSkip[curr], prevSkip[prev] + score);

          } else {
            long long score = prefix[j][prev] - prefix[j][curr];

            currPick[curr] = max(currPick[curr], prevPick[prev] + score);
            currSkip[curr] = max(currSkip[curr], prevPick[prev]);
          }
        }
      }

      prevPick = currPick;
      prevSkip = currSkip;
    }

    return *max_element(prevPick.begin(), prevPick.end());
  }
};
```

---

## Professional Refactor

```cpp
// 3225. Maximum Score From Grid Operations
// O(n³) time, O(n) extra space
class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        const int n = grid.size();
        // column‑wise prefix sums
        vector<vector<long long>> pref(n, vector<long long>(n + 1, 0));
        for (int col = 0; col < n; ++col)
            for (int row = 0; row < n; ++row)
                pref[col][row + 1] = pref[col][row] + grid[row][col];

        const long long NEG = LLONG_MIN / 4;
        vector<long long> dpPrev(n + 1, 0), dpCurr(n + 1, NEG);

        // process columns 1 … n‑1
        for (int col = 1; col < n; ++col) {
            fill(dpCurr.begin(), dpCurr.end(), NEG);
            for (int h = 0; h <= n; ++h) {          // current height
                for (int p = 0; p <= n; ++p) {      // previous height
                    long long gain = 0;
                    if (h <= p) { // shrink or keep black prefix
                        gain = pref[col - 1][p] - pref[col - 1][h];
                    }
                    dpCurr[h] = max(dpCurr[h], dpPrev[p] + gain);
                }
            }
            dpPrev.swap(dpCurr);
        }

        return *max_element(dpPrev.begin(), dpPrev.end());
    }
};
```

---

## Code Walkthrough  

* **Prefix construction** (`pref[col][k]`) – enables `O(1)` interval sum `pref[col][r] - pref[col][l]`.  
* **DP arrays** – `dpPrev[h]` stores the best score up to the previous column with height `h`. Only two 1‑D arrays are needed (`dpCurr` for the new column).  
* **Transition loop** – iterates over every pair `(p, h)`.  
  * When `h ≤ p` the interval `[h, p)` contributes `pref[col‑1][p] - pref[col‑1][h]`.  
  * When `h > p` the contribution is zero (expanding the black prefix never yields points).  
* **Result** – after the last column, the maximum over all possible final heights is the answer.  

The refactor removes the auxiliary `prevPick / prevSkip` distinction, uses a clear `gain` variable, and adds comments for readability while preserving the exact $O(n^{3})$ DP logic.
