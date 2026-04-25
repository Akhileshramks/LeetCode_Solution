# 343. Integer Break

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** April 25, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 3 ms &nbsp;|&nbsp; **Memory:** 9.7 MB

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

The product is maximized when the summands are as **close to $e$** as possible.  
Because we must use *integers*, the optimal integer close to $e$ is **$3$**.  
Thus we should split $n$ into as many $3$’s as we can.  
The only exception is when the remainder after extracting $3$’s is **$1$** – a factor $1$ never helps, so we replace one $3+1$ by **$2+2$**.  
This greedy choice is provably optimal by the inequality $3\cdot (x-3) \ge x$ for all $x\ge5$.

## Approach

1. **Handle small $n$ directly**  
   * $n=2 \rightarrow 1$ (only $1+1$)  
   * $n=3 \rightarrow 2$ (best split $1+2$)  

2. **Greedy extraction of 3’s**  
   * While $n > 4$, multiply answer by $3$ and set $n \leftarrow n-3$.  
   * The loop stops when the remaining $n$ is $2$, $3$, or $4$ – all of which should be taken as a whole (no further split improves the product).

3. **Multiply the leftover**  
   * Return `ans * n`.

## Complexity Analysis

|            | Complexity | Reason                                   |
|------------|------------|------------------------------------------|
| **Time**   | $O(n)$ ≈ $O(1)$ | Each iteration reduces $n$ by $3$; at most $n/3$ steps. |
| **Space**  | $O(1)$     | Only a few scalar variables are used.   |

## Key Takeaways

- **Maximum‑product split = many 3’s** – the integer closest to $e$ yields the highest multiplicative gain.  
- **Remainder $1$ is fatal**; convert a trailing `3+1` into `2+2` to avoid a factor of $1$.  
- **Greedy proof via local optimality**: replacing any part $x\ge5$ by $3+(x-3)$ never decreases the product, guaranteeing global optimality.  
- **DP is overkill** for this problem; a constant‑time greedy solution is both simpler and faster.

## My Original Solution

```cpp
class Solution {
public:
    int findMaxProduct(vector<int>& nums, int ind, int target,vector<vector<int>> &dp){
        if(target == 0) return 1;
        if(ind  == 0) return target % nums[ind] == 0 ? (int)pow(nums[ind], target / nums[ind]) : 0;
        if(ind < 0) return 0;
        if(dp[ind][target] != -1) return dp[ind][target];
        int notTake = findMaxProduct(nums, ind-1, target, dp);
        int take = 0;
        if(nums[ind] <= target){
            take = findMaxProduct(nums, ind, target-nums[ind], dp);
        }
        take *= nums[ind];
        return dp[ind][target] = max(take, notTake);
    }
    int integerBreak(int n) {
        vector<int> nums;
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        for(int i = 1;i < n;i++) nums.push_back(i);
        return findMaxProduct(nums, n-2, n, dp);
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int integerBreak(int n) {
        // Base cases: we must break the number into at least two parts.
        if (n == 2) return 1;          // 1 + 1
        if (n == 3) return 2;          // 1 + 2

        int product = 1;
        // Extract as many 3's as possible while keeping n > 4.
        while (n > 4) {
            product *= 3;
            n -= 3;
        }
        // The remaining n (2, 3, or 4) is multiplied directly.
        product *= n;
        return product;
    }
};
```

## Code Walkthrough

- **Base handling (`n == 2` / `n == 3`)** – the problem forces at least two summands, so we cannot return `n` itself.
- **Greedy loop** – each iteration replaces a segment `x ≥ 5` by `3 + (x‑3)`.  
  The product change is `3·(x‑3) ≥ x`, guaranteeing we never worsen the answer.
- **Termination condition (`n <= 4`)** – at this point any further split would introduce a factor `1` or reduce the product, so we safely multiply the leftover `n` in one go.
