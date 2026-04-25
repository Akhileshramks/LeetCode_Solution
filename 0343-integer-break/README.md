# 343. Integer Break

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** April 25, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 7.9 MB

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

The product of summands grows fastest when each summand is as close to the mathematical constant $e\approx2.718$ as possible.  
Since we can only use **integers**, the nearest integer to $e$ is $3$.  
Therefore, for any $n>4$, replacing a part $x\ge5$ by $3+(x-3)$ always increases the product:
\[
3\cdot(x-3) \;>\; x \quad\text{for }x\ge5.
\]
Consequently the optimal decomposition consists of as many $3$'s as possible, with a leftover of $2$ or $4$ (both of which are already optimal).  
The only tricky part is handling the small base cases $n\le4$, where breaking would *decrease* the product.

---

## Approach

1. **Handle base cases**  
   * $n=2\rightarrow 1$ (must split into $1+1$).  
   * $n=3\rightarrow 2$ (split into $1+2$).  
   * $n=4\rightarrow 4$ (either $2+2$ or keep as $4$ after a previous split).  

2. **Greedy decomposition**  
   * Initialise `product = 1`.  
   * While $n>4$, subtract $3$ from $n$ and multiply `product` by $3`.  
   * After the loop, `n` is $2$, $3$, or $4`; multiply `product` by this remainder.

3. **Return** the accumulated product.

---

## Complexity Analysis

|            | Complexity | Reason                                            |
|------------|------------|---------------------------------------------------|
| **Time**   | $O(n)$     | Each iteration reduces $n$ by $3$ → at most $\lceil n/3\rceil$ steps |
| **Space**  | $O(1)$     | Only a few scalar variables are used               |

---

## Key Takeaways

- **Greedy optimality proof**: For integer partitions, repeatedly extracting a $3$ never harms optimality because $3\cdot(x-3) > x$ for $x\ge5$.
- **Edge‑case vigilance**: The generic greedy rule fails for $n\le4$; those values must be hard‑coded.
- **Mathematical grounding**: The constant $e$ guides the choice of $3$; recognizing this link turns a DP‑style problem into an $O(1)$‑space greedy solution.
- **Avoiding DP overhead**: Although a classic DP formulation exists, the greedy insight eliminates the $O(n^2)$ DP table entirely.

---

## My Original Solution

```cpp
class Solution {
public:
    int integerBreak(int n) {
        // vector<int> dp(n+1, 0);
        // dp[1] = 1;
        // for(int i = 2;i <= n;i++){
        //     for(int j = 1;j < i;j++){
        //         dp[i] = max(dp[i], max(dp[i-j] * j, j * (i-j)));
        //     }
        // }
        // return dp[n];

        // When n > 4, the number 3 gives the highest product
        int product = 1;
        if(n == 1) return 1;
        else if(n < 4) return n-1;
        else if(n == 4) return 4;
        while(n > 4){
            n-=3;
            product *= 3;
        }
        return product * n;
    }
};
```

## Professional Refactor

```cpp
// cpp
class Solution {
public:
    int integerBreak(int n) {
        // Base cases where breaking reduces the product
        if (n == 2) return 1;          // 1 + 1
        if (n == 3) return 2;          // 1 + 2
        if (n == 4) return 4;          // 2 + 2 (or keep as 4 after previous split)

        long long product = 1;         // use 64‑bit to avoid overflow for intermediate steps

        // Greedily take as many 3's as possible
        while (n > 4) {
            product *= 3;
            n -= 3;
        }

        // Multiply the remaining 2, 3 or 4
        product *= n;
        return static_cast<int>(product);
    }
};
```

## Code Walkthrough

- **Base case block** (`n == 2/3/4`): Directly returns the known optimal products; these are the only values where the greedy rule would incorrectly split the number.
- **`while (n > 4)` loop**: Each iteration extracts a factor of $3$, the proven optimal summand, and reduces `n` accordingly. The loop runs at most $\lceil n/3\rceil$ times.
- **Final multiplication**: After the loop, the leftover `n` is $2$, $3$, or $4$, all of which are already optimal as a single factor. Multiplying `product` by this remainder yields the maximum possible product.
