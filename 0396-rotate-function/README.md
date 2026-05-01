# 396. Rotate Function

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 1, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 99.7 MB

---

## Problem

You are given an integer array `nums` of length `n`.

Assume `arrk` to be an array obtained by rotating `nums` by `k` positions clock-wise. We define the **rotation function** `F` on `nums` as follow:

	
- `F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1].`

Return _the maximum value of_ `F(0), F(1), ..., F(n-1)`.

The test cases are generated so that the answer fits in a **32-bit** integer.

 

**Example 1:**

> **Input:** nums = [4,3,2,6]
> **Output:** 26
> **Explanation:**
> F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
> F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
> F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
> F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
> So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.

**Example 2:**

> **Input:** nums = [100]
> **Output:** 0

## Constraints

- `n == nums.length`
	
- `1 <= n <= 105`
	
- `-100 <= nums[i] <= 100`

## Hints

_No hints provided._

---

## Intuition

The key insight is that consecutive rotation values are linearly related.  
If we know $F(k-1)$, rotating the array one step further moves the last element of the previous rotation to the front. This changes the weighted sum by **adding the total sum of the array** (every element’s coefficient increases by 1) and **subtracting $n$ times the element that wrapped around** (its coefficient drops from $n-1$ to $0$).  
Hence  

\[
F(k)=F(k-1)+\text{sum}-n\cdot \text{nums}[n-k]
\]

With this recurrence we can compute all $F(k)$ in $O(n)$ time instead of the naïve $O(n^2)$.

---

## Approach

1. Compute the total sum of the array: $\text{sum}= \sum_{i=0}^{n-1}\text{nums}[i]$.
2. Compute the initial rotation function $F(0)=\sum_{i=0}^{n-1} i\cdot\text{nums}[i]$.
3. Initialise the answer with $F(0)$.
4. Iterate $k$ from 1 to $n-1$:
   - Update $F(k)$ using the recurrence  
     $F(k)=F(k-1)+\text{sum}-n\cdot\text{nums}[n-k]$.
   - Keep the maximum value seen so far.
5. Return the maximum.

---

## Complexity Analysis

|               | Complexity | Reason                                   |
|---------------|------------|------------------------------------------|
| **Time**      | $O(n)$     | One pass for the sum, one pass for $F(k)$ |
| **Space**     | $O(1)$     | Only a few scalar variables are used      |

---

## Key Takeaways

- Deriving a recurrence between successive rotation functions turns an $O(n^2)$ brute‑force into $O(n)$.
- The recurrence only needs the **total sum** and the element that moves from the end to the front; no extra arrays are required.
- Even though the problem guarantees a 32‑bit answer, using a wider type (e.g., `long long`) prevents overflow during intermediate calculations.
- The same pattern appears in other “rotating‑weighted‑sum” problems—look for a linear relationship when the window slides by one position.

---

## My Original Solution

```cpp
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int prev = 0;
        for(int i = 0;i < n;i++) prev += i * nums[i];
        int res = prev;
        for(int i = 1;i < n;i++){
            int new_prev = prev + sum - n * nums[n-i];
            res = max(res, new_prev);
            prev = new_prev;
        }
        return res;
    }
};
```

---

## Professional Refactor

```cpp
class Solution {
public:
    int maxRotateFunction(const vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        if (n == 1) return 0;                     // trivial case

        long long totalSum = 0;
        long long f0 = 0;
        for (int i = 0; i < n; ++i) {
            totalSum += nums[i];
            f0 += static_cast<long long>(i) * nums[i];
        }

        long long maxVal = f0;
        long long cur = f0;
        for (int k = 1; k < n; ++k) {
            // element that moves to the front is nums[n - k]
            cur = cur + totalSum - static_cast<long long>(n) * nums[n - k];
            maxVal = max(maxVal, cur);
        }
        return static_cast<int>(maxVal);
    }
};
```

---

## Code Walkthrough

- **`totalSum`** accumulates $\sum_{i=0}^{n-1}\text{nums}[i]$, needed for every recurrence step.  
- **`f0`** computes $F(0)=\sum i\cdot\text{nums}[i]$ in a single pass.  
- The loop `for (int k = 1; k < n; ++k)` applies the recurrence  
  `cur = cur + totalSum - n * nums[n - k]`  
  where `nums[n - k]` is the element that wrapped from the end to the front after the $k^{\text{th}}$ rotation.  
- `maxVal` tracks the maximum $F(k)$ encountered; the final cast back to `int` is safe per the problem statement.
