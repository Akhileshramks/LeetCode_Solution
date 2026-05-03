# 2719. Count of Integers

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Math, String, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 3, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 151 ms &nbsp;|&nbsp; **Memory:** 105.8 MB

---

## Problem

You are given two numeric strings `num1` and `num2` and two integers `max_sum` and `min_sum`. We denote an integer `x` to be _good_ if:

	
- `num1 <= x <= num2`
	
- `min_sum <= digit_sum(x) <= max_sum`.

Return _the number of good integers_. Since the answer may be large, return it modulo `109 + 7`.

Note that `digit_sum(x)` denotes the sum of the digits of `x`.

 

**Example 1:**

> **Input:** num1 = "1", num2 = "12", `min_sum` = 1, max_sum = 8
> **Output:** 11
> **Explanation:** There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.

**Example 2:**

> **Input:** num1 = "1", num2 = "5", `min_sum` = 1, max_sum = 5
> **Output:** 5
> **Explanation:** The 5 integers whose sum of digits lies between 1 and 5 are 1,2,3,4, and 5. Thus, we return 5.

## Constraints

- `1 <= num1 <= num2 <= 1022`
	
- `1 <= min_sum <= max_sum <= 400`

## Hints

1. Let f(n, l, r) denotes the number of integers from 1 to n with the sum of digits between l and r.
2. The answer is f(num2, min_sum, max_sum) - f(num1-1, min_sum, max_sum).
3. You can calculate f(n, l, r) using digit dp.

---

## Intuition

The task is to count numbers in a **continuous numeric interval** whose digit‑sum lies inside a given range.  
The classic way to answer “how many numbers ≤ X satisfy a digit property?” is **digit DP**: we walk the decimal representation from most to least significant digit, keep a flag (`tight`) that tells whether we are still on the prefix of X, and accumulate the current digit sum.  

The only extra hurdle is that the interval is **closed** `[num1, num2]`.  
Counting up to `num2` is straightforward; counting up to `num1‑1` requires a safe **string‑based decrement** because the bounds can be up to 10²² (far beyond 64‑bit).  
The answer is `cnt(num2) − cnt(num1‑1)` modulo $10^9\!+\!7$.

The “aha” moment is realizing that the digit‑sum constraint is **independent of the actual value** once the prefix is fixed, so it can be stored as a DP dimension (`sum`). This yields a DP of size `length × 2 × (max_sum+1)`, which easily fits the limits (`max_sum ≤ 400`).

---

## Approach

1. **Prepare the lower bound**  
   * Convert `num1` to `num1‑1` by scanning from the least significant digit, borrowing as needed, and removing a leading zero if it appears.

2. **Define the DP**  
   * `dfs(pos, tight, sum)` – number of ways to fill positions `[pos … end)`  
     * `pos` – current index (0‑based, left to right)  
     * `tight` – `1` if the prefix so far equals the prefix of the bound, otherwise `0` (we may use any digit `0…9`)  
     * `sum` – accumulated digit sum so far (pruned when `sum > max_sum`)

3. **Transition**  
   * `limit = tight ? bound[pos] – '0' : 9`  
   * For each digit `d ∈ [0, limit]`  
     * `new_tight = tight && (d == limit)`  
     * Recurse to `dfs(pos+1, new_tight, sum+d)` and add the result modulo $M$.

4. **Base case**  
   * When `pos == bound.length()`, return `1` iff `min_sum ≤ sum ≤ max_sum`, else `0`.

5. **Memoization**  
   * Store results in `dp[pos][tight][sum]` (initialized to `-1`).  
   * The DP is rebuilt separately for `num2` and `num1‑1` because the bound length may differ.

6. **Combine**  
   * `ans = (cnt(num2) – cnt(num1‑1) + M) % M`.

---

## Complexity Analysis

|                | Complexity                              | Reason                                                                 |
|----------------|------------------------------------------|------------------------------------------------------------------------|
| **Time**       | $O(L \times S \times 10)$                | `L = length(bound) ≤ 22`, `S = max\_sum ≤ 400`; each state iterates over at most 10 digits |
| **Space**      | $O(L \times S)$                          | DP table `dp[L][2][S+1]`; the `tight` dimension is constant `2`        |

(The factor `10` is absorbed into the constant; the asymptotic bound is $O(L·S)$.)

---

## Key Takeaways

* **Digit DP works on arbitrary‑length strings** – you never need to convert the bound to an integer; the algorithm operates directly on the character array.
* **Subtract‑one on a decimal string** is a reusable utility when dealing with inclusive intervals that cannot be represented numerically.
* **Early pruning** (`if sum > max_sum return 0`) dramatically reduces the state space because `max_sum` is small relative to the number of possible digit combinations.
* **Separate DP tables per bound** avoid cross‑contamination when the two bounds have different lengths; reusing the same table would require resetting or a more complex indexing scheme.

---

## My Original Solution

```cpp
class Solution {
public:
    int MOD = 1e9 + 7;
    string subtrackOne(string s){
        if(s == "0") return s;
        int n = s.size();
        int i = n - 1;
        while(i >= 0 && s[i] == '0'){
            s[i] = '9';
            i--;
        }
        if(i >= 0) s[i]--;

        if(s[0] == '0' && s.size() > 1){
            s = s.substr(1);
        }
        return s;
    }
    long long countDigitSum(string s, int ind, int tight, int sum, int minSum, int maxSum, vector<vector<vector<long long>>>& dp){
        if(sum > maxSum) return 0;
        if(ind == s.size()){
            if(sum >= minSum && sum <= maxSum) return 1;
            return 0;
        }
        if(dp[ind][tight][sum] != -1) return dp[ind][tight][sum];
        int limit = tight ? s[ind] - '0' : 9;
        long long res = 0;
        for(int i = 0;i <= limit; i++){
            int new_tight = (tight & (s[ind] - '0' == i));
            res = (res + countDigitSum(s, ind + 1, new_tight, sum + i, minSum, maxSum, dp)) % MOD;
        }
        return dp[ind][tight][sum] = res;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        num1 = subtrackOne(num1);
        int n = num2.size();
        vector<vector<vector<long long>>> dp1(n + 1, vector<vector<long long>>(2, vector<long long>(401, -1)));
        vector<vector<vector<long long>>> dp2(n + 1, vector<vector<long long>>(2, vector<long long>(401, -1)));
        long long r = countDigitSum(num2, 0, 1, 0, min_sum, max_sum, dp1);
        long long l = countDigitSum(num1, 0, 1, 0, min_sum, max_sum, dp2);
        return (r - l + MOD) % MOD;
    }
};
```

## Professional Refactor

```cpp
// language: cpp
class Solution {
    static constexpr int MOD = 1'000'000'007;
    static constexpr int MAX_SUM = 400;          // given constraint

    // Decrement a non‑negative decimal string by one.
    string decOne(string s) {
        int i = (int)s.size() - 1;
        while (i >= 0 && s[i] == '0') {
            s[i] = '9';
            --i;
        }
        if (i >= 0) --s[i];                       // guaranteed s != "0"
        if (s.front() == '0' && s.size() > 1)     // remove leading zero
            s.erase(s.begin());
        return s;
    }

    // Digit DP: count numbers ≤ bound with digit‑sum in [lo, hi].
    long long dfs(const string& bound, int pos, bool tight, int sum,
                  int lo, int hi,
                  vector<vector<vector<int>>>& memo) const {

        if (sum > hi) return 0;                    // pruning
        if (pos == (int)bound.size())
            return (lo <= sum && sum <= hi) ? 1 : 0;

        int& cached = memo[pos][tight][sum];
        if (cached != -1) return cached;

        int limit = tight ? bound[pos] - '0' : 9;
        long long ans = 0;
        for (int d = 0; d <= limit; ++d) {
            bool ntight = tight && (d == limit);
            ans += dfs(bound, pos + 1, ntight, sum + d, lo, hi, memo);
            if (ans >= MOD) ans -= MOD;
        }
        return cached = (int)ans;
    }

    // Helper that builds a fresh memo table for a given bound.
    long long countUpTo(const string& bound, int lo, int hi) const {
        int n = bound.size();
        vector<vector<vector<int>>> memo(
            n, vector<vector<int>>(2, vector<int>(MAX_SUM + 1, -1)));
        return dfs(bound, 0, true, 0, lo, hi, memo);
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        string left = decOne(num1);                // inclusive lower bound → exclusive after decrement
        long long high = countUpTo(num2, min_sum, max_sum);
        long long low  = countUpTo(left, min_sum, max_sum);
        long long res = (high - low) % MOD;
        if (res < 0) res += MOD;
        return (int)res;
    }
};
```

## Code Walkthrough

* **`decOne`** – walks from the least significant digit, flips trailing `0`s to `9`s (borrow), decrements the first non‑zero digit, and strips a possible leading zero. This yields `num1‑1` without overflow.
* **`dfs`** – the heart of the digit DP.  
  * `tight` tells whether the current prefix is exactly the prefix of `bound`. If `tight` is `true`, the next digit cannot exceed `bound[pos]`; otherwise we may use any digit `0…9`.  
  * `sum` accumulates the digit sum; we abort early when it exceeds `max_sum`.  
  * The memo table `memo[pos][tight][sum]` stores the result modulo $M$; `-1` marks “uncomputed”.
* **`countUpTo`** – allocates a fresh memo table sized to the current bound and launches `dfs` from the most significant digit.
* **`count`** – obtains `cnt(num2)` and `cnt(num1‑1)`, subtracts them, normalizes the result into `[0, M)`, and returns the final count.

The refactor isolates responsibilities, uses fixed‑size containers (`int` for memo because values are already reduced modulo $M$), and adds clear comments, making the solution easier to read and maintain.
