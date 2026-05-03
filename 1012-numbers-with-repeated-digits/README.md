# 1012. Numbers With Repeated Digits

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 3, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 402 ms &nbsp;|&nbsp; **Memory:** 147.7 MB

---

## Problem

Given an integer `n`, return _the number of positive integers in the range _`[1, n]`_ that have **at least one** repeated digit_.

 

**Example 1:**

> **Input:** n = 20
> **Output:** 1
> **Explanation:** The only positive number ( **Input:** n = 100
> **Output:** 10
> **Explanation:** The positive numbers ( **Input:** n = 1000
> **Output:** 262

## Constraints

- `1 <= n <= 109`

## Hints

1. How many numbers with no duplicate digits?  How many numbers with K digits and no duplicates?
2. How many numbers with same length as N?  How many numbers with same prefix as N?

---

## Intuition

The problem asks for numbers **with at least one repeated digit** in \([1,n]\).  
It is far easier to count the complementary set – numbers that have **all distinct digits** – because a distinct‑digit constraint can be expressed as a simple “used‑digit” mask.  
If we can compute  

\[
\text{unique}(n)=\#\{\text{numbers in }[1,n]\text{ with no repeated digit}\},
\]

then the answer is simply  

\[
\text{answer}=n-\text{unique}(n).
\]

Thus the core insight is: *turn a “hard” counting problem into a classic digit‑DP that tracks which digits have already appeared*.

## Approach

1. **Convert \(n\) to a string** `s` so we can process it digit by digit from most significant to least.  
2. **Define a memoized recursive DP** `dfs(pos, tight, mask, started)` that returns the number of ways to fill the suffix starting at `pos`:
   - `pos` – current index in `s`.  
   - `tight` – `1` if the prefix built so far equals the prefix of `s`; otherwise `0` (we may use any digit ≤ 9).  
   - `mask` – 10‑bit bitmask; bit \(d\) set ⇔ digit \(d\) has already been used in the current number.  
   - `started` – `1` once we have placed a non‑leading‑zero digit; before that we are still “skipping” leading zeros.
3. **Transition**  
   - Determine the upper bound `limit = tight ? s[pos]-'0' : 9`.  
   - Iterate `dig` from `0` to `limit`.  
   - Compute `newTight = tight && (dig == limit)`.  
   - If `!started && dig == 0`, we stay in the “not started” state; the mask stays unchanged because leading zeros do not count as used digits.  
   - Otherwise (`started` becomes `1`):  
     - If `mask` already contains `dig`, we **skip** this branch because it would create a repeated digit (we are counting only distinct‑digit numbers).  
     - Otherwise set `newMask = mask | (1 << dig)` and recurse.
4. **Base case**: when `pos == s.size()`, return `started ? 1 : 0` (a valid positive number has been formed).  
5. **Result**: `unique = dfs(0, 1, 0, 0)`. Final answer = `n - unique`.

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(L \times 2^{10} \times 10)$ ≈ $O(L \cdot 2^{10})$ | `L = number of digits of n` (≤ 10). For each position we iterate up to 10 digits and memoize over `tight (2) × started (2) × mask (2^{10})`. |
| **Space**      | $O(L \times 2^{10})$ | DP table stores one integer per state `(pos, tight, started, mask)`. |

## Key Takeaways

- **Complement counting**: When “at least one” conditions are hard, count the opposite (“none”) and subtract.  
- **Bitmask for digit usage**: With only 10 possible digits, a 10‑bit mask gives $O(1)$ checks for repeats and fits comfortably into DP state space.  
- **Tight flag**: Guarantees we never exceed the upper bound `n` while still allowing free choice once the prefix is already smaller.  
- **Leading‑zero handling**: A separate `started` flag prevents leading zeros from being treated as used digits, ensuring numbers like `0012` are counted as `12`.
