# 2033. Minimum Operations to Make a Uni-Value Grid

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Math, Sorting, Matrix &nbsp;|&nbsp; **Solved:** April 28, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 44 ms &nbsp;|&nbsp; **Memory:** 87 MB

---

## Problem

You are given a 2D integer `grid` of size `m x n` and an integer `x`. In one operation, you can **add** `x` to or **subtract** `x` from any element in the `grid`.

A **uni-value grid** is a grid where all the elements of it are equal.

Return _the **minimum** number of operations to make the grid **uni-value**_. If it is not possible, return `-1`.

 

**Example 1:**

![](https://assets.leetcode.com/uploads/2021/09/21/gridtxt.png)

> **Input:** grid = [[2,4],[6,8]], x = 2
> **Output:** 4
> **Explanation:** We can make every element equal to 4 by doing the following: 
> - Add x to 2 once.
> - Subtract x from 6 once.
> - Subtract x from 8 twice.
> A total of 4 operations were used.

**Example 2:**

![](https://assets.leetcode.com/uploads/2021/09/21/gridtxt-1.png)

> **Input:** grid = [[1,5],[2,3]], x = 1
> **Output:** 5
> **Explanation:** We can make every element equal to 3.

**Example 3:**

![](https://assets.leetcode.com/uploads/2021/09/21/gridtxt-2.png)

> **Input:** grid = [[1,2],[3,4]], x = 2
> **Output:** -1
> **Explanation:** It is impossible to make every element equal.

## Constraints

- `m == grid.length`
	
- `n == grid[i].length`
	
- `1 <= m, n <= 105`
	
- `1 <= m * n <= 105`
	
- `1 <= x, grid[i][j] <= 104`

## Hints

1. Is it possible to make two integers a and b equal if they have different remainders dividing by x?
2. If it is possible, which number should you select to minimize the number of operations?
3. What if the elements are sorted?

---

## Intuition

The operation changes any cell by exactly $x$, so each element can only reach values that are congruent to its original value modulo $x$.  
Therefore, a necessary (and sufficient) condition for a uni‑value grid is that **all cells share the same remainder when divided by $x$**.  
Once this condition holds, the problem reduces to moving each number to a common target using steps of size $x$.  
If we view each element as a point on the number line and count the number of steps as the **$L_1$ distance divided by $x$**, the optimal target is the **median** of the values (the point that minimizes the sum of absolute deviations).  

The “aha!” moment is recognizing that the median—computed on the original values, not on the values divided by $x$—directly yields the minimal total operations.

---

## Approach

1. **Flatten & Mod‑Check**  
   - Traverse the grid, push every element into a 1‑D vector `vals`.  
   - Record `base = grid[0][0] % x`.  
   - If any element `v` satisfies `v % x != base`, return `-1` (impossible).

2. **Sort & Median**  
   - Sort `vals`.  
   - Let `median = vals[sz/2]` (for even `sz`, any of the two middle values works).

3. **Count Operations**  
   - For each `v` in `vals`, add `abs(v - median) / x` to the answer.  
   - Return the accumulated sum.

---

## Complexity Analysis

|                | Complexity | Reason |
|----------------|------------|--------|
| **Time**       | $O(mn \log(mn))$ | Flattening takes $O(mn)$, sorting dominates with $O(mn \log(mn))$. |
| **Space**      | $O(mn)$ | The flattened vector stores all $mn$ elements. |

---

## Key Takeaways

- **Modulo uniformity** is the only feasibility gate: all numbers must be in the same residue class modulo $x$.  
- The **median** of the original values minimizes the total number of $x$‑steps because it minimizes the sum of absolute differences ($L_1$ norm).  
- Converting the distance to **operations** is simply `abs(a‑b) / x`; no need to actually simulate each addition/subtraction.  
- Flattening a matrix into a vector and sorting it is acceptable under the constraint $m \cdot n \le 10^5$, keeping both time and memory within limits.
