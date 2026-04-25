# 343. Integer Break

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** April 25, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 8.5 MB

---

## Problem

Given an integer `n`, break it into the sum of `k` **positive integers**, where `k >= 2`, and maximize the product of those integers.

Return _the maximum product you can get_.

 

**Example 1:**

> **Input:** n = 2
> **Output:** 1
> **Explanation:** 2 = 1 + 1, 1 &times; 1 = 1.

**Example 2:**

> **Input:** n = 10
> **Output:** 36
> **Explanation:** 10 = 3 + 3 + 4, 3 &times; 3 &times; 4 = 36.

## Constraints

- `2 <= n <= 58`

## Hints

1. There is a simple O(n) solution to this problem.
2. You may check the breaking results of _n_ ranging from 7 to 10 to discover the regularities.

---

## Intuition

The product is maximized when each summand is as close to $e\approx2.718$ as possible.  
For integers this translates to using as many $3$’s as we can; a leftover $2$ (or $4=2+2$) is better than a leftover $1$.  
Dynamic programming captures exactly this “break‑or‑keep” choice: for each $i$ we decide whether to keep a part $j$ as is (`j * (i‑j)`) or to break the remainder further (`j * dp[i‑j]`). The optimal product for $i$ is the maximum over all $j$.

## Approach

1. Create a DP array `dp` where `dp[i]` stores the maximum product obtainable by breaking integer $i$ (with at least two parts).  
2. Initialise `dp[1] = 1` (base case for recursion).  
3. Iterate `i` from $2$ to $n$:  
   - For each possible first part `j` (`1 ≤ j < i`), compute two candidates:  
     * `j * (i‑j)` – keep the remainder as a single piece.  
     * `j * dp[i‑j]` – break the remainder further using the already‑computed optimum.  
   - Update `dp[i]` with the larger of the current value and the two candidates.  
4. Return `dp[n]`.

## Complexity Analysis

|               | Complexity | Reason                                                                      |
|---------------|------------|-----------------------------------------------------------------------------|
| **Time**      | $O(n^2)$   | Double loop: outer $i$ runs $n$ times, inner $j$ runs up to $i‑1$ times. |
| **Space**     | $O(n)$     | One DP array of length $n+1$.                                                |

## Key Takeaways

- **Break‑or‑keep recurrence**: `dp[i] = max_{1≤j<i} ( max(j * (i‑j), j * dp[i‑j]) )` cleanly encodes the decision to stop breaking or continue recursively.  
- **Implicit greedy insight**: The DP naturally discovers the optimal “use as many $3$’s as possible” pattern without hard‑coding it.  
- **Base case nuance**: Setting `dp[1]=1` (instead of $0$) allows the recurrence to correctly handle the smallest breakable piece.  
- **Small constraints, quadratic DP**: With $n ≤ 58$, $O(n^2)$ is trivial, but the same recurrence scales to larger $n$ if needed.

## My Original Solution

```cpp
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for(int i = 2;i <= n;i++){
            for(int j = 1;j < i;j++){
                dp[i] = max(dp[i], max(dp[i-j] * j, j * (i-j)));
            }
        }
        return dp[n];
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int integerBreak(int n) {
        // dp[i] = maximum product for integer i (must be split into at least two parts)
        vector<int> dp(n + 1, 0);
        dp[1] = 1;                     // base case: 1 can only be "1 * 1"

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                // Option 1: keep (i - j) as a whole number
                int keep = j * (i - j);
                // Option 2: further break (i - j) using previously computed optimum
                int breakFurther = j * dp[i - j];
                dp[i] = max(dp[i], max(keep, breakFurther));
            }
        }
        return dp[n];
    }
};
```

## Code Walkthrough

- **DP definition**: `dp[i]` stores the best product achievable by splitting `i` into **at least two** positive integers.  
- **Inner update**:  
  ```cpp
  int keep = j * (i - j);          // no further split of the remainder
  int breakFurther = j * dp[i - j]; // recurse on the remainder
  dp[i] = max(dp[i], max(keep, breakFurther));
  ```  
  This line embodies the core “break‑or‑keep” decision.  
- **Loop bounds**: `j` runs from `1` to `i‑1` to ensure both parts are positive; the outer loop builds solutions bottom‑up so `dp[i‑j]` is already known.  
- **Return**: After filling the table, `dp[n]` holds the answer for the original integer.
