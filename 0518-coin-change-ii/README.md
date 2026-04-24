# 518. Coin Change II

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming &nbsp;|&nbsp; **Solved:** April 24, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 43 ms &nbsp;|&nbsp; **Memory:** 60.5 MB

---

## Problem

You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return _the number of combinations that make up that amount_. If that amount of money cannot be made up by any combination of the coins, return `0`.

You may assume that you have an infinite number of each kind of coin.

The answer is **guaranteed** to fit into a signed **32-bit** integer.

 

**Example 1:**

> **Input:** amount = 5, coins = [1,2,5]
> **Output:** 4
> **Explanation:** there are four ways to make up the amount:
> 5=5
> 5=2+2+1
> 5=2+1+1+1
> 5=1+1+1+1+1

**Example 2:**

> **Input:** amount = 3, coins = [2]
> **Output:** 0
> **Explanation:** the amount of 3 cannot be made up just with coins of 2.

**Example 3:**

> **Input:** amount = 10, coins = [10]
> **Output:** 1

## Constraints

- `1 <= coins.length <= 300`
	
- `1 <= coins[i] <= 5000`
	
- All the values of `coins` are **unique**.
	
- `0 <= amount <= 5000`

## Hints

_No hints provided._

---

## Intuition

The “aha!” moment is to treat the problem as an **unbounded knapsack counting** task where the order of coins does **not** matter.  
If we process the coin denominations one by one and, for each coin, update the number of ways to reach every amount `a` using the relation  

\[
\text{dp}[a] \leftarrow \text{dp}[a] + \text{dp}[a - \text{coin}]
\]

we automatically avoid counting permutations of the same multiset of coins. The DP state \(\text{dp}[a]\) therefore represents *the number of combinations that sum to* \(a\) *using only the coins we have already processed*. This insight lets us collapse the two‑dimensional recursion into a single 1‑D array, achieving both correctness and optimal space usage.

## Approach

1. **Initialize** a 1‑D array `dp[0…amount]` with `dp[0] = 1` (one way to make amount 0) and the rest 0.  
2. **Iterate** over each coin `c` in `coins` (outer loop).  
3. For the current coin, **traverse** amounts from `c` up to `amount` (inner loop).  
   - Update `dp[a] += dp[a - c]`.  
   - `dp[a - c]` already contains the count of ways to make `a - c` using the current coin **and** all previously processed coins, so adding it extends those ways with one extra `c`.  
4. After processing all coins, `dp[amount]` holds the required number of combinations.  

The algorithm is exactly the classic *unbounded knapsack* DP but with the inner loop iterating **ascending** to allow reuse of the same coin unlimited times.

## Complexity Analysis

|               | Complexity | Reason                                                                 |
|---------------|------------|------------------------------------------------------------------------|
| **Time**      | $O(n \cdot A)$ | `n = coins.size()`, `A = amount`; each coin scans all amounts once. |
| **Space**     | $O(A)$     | One 1‑D array of size `amount + 1`.                                     |

## Key Takeaways

- **Order‑independent counting**: looping over coins **outside** the amount loop guarantees each combination is counted exactly once, eliminating duplicate permutations.  
- **Unbounded knapsack DP** works with a *single* array when the inner loop runs forward; this is the same trick used for the “Coin Change” minimum‑coins problem but with additive accumulation.  
- **Base case `dp[0] = 1`** is crucial—it represents the empty‑coin combination and seeds all subsequent updates.  
- **Use `long long` for intermediate sums** because intermediate counts may exceed 32‑bit range even though the final answer is guaranteed to fit in an `int`.

## My Original Solution

```cpp
class Solution {
public:
    int countPossible(vector<int> coins, int ind, int amount, vector<vector<int>>& dp){
        if(ind == 0) return amount % coins[ind] == 0;
        if(ind < 0) return 0;
        if(dp[ind][amount] != -1) return dp[ind][amount];
        int notTake = countPossible(coins, ind - 1, amount, dp);
        int take = 0;
        if(coins[ind] <= amount){
            take = countPossible(coins, ind, amount - coins[ind], dp);
        }
        return dp[ind][amount] = take + notTake;
    }
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<long long> prev(amount+1, 0);
        for(int i = 0;i <= amount;i++) prev[i] = (i % coins[0] == 0);
        for(int ind = 1;ind < n;ind++){
            vector<long long> curr(amount+1, 0);
            for(int remaining = 0; remaining <= amount;remaining++){
                int notTake = prev[remaining];
                int take = 0;
                if(coins[ind] <= remaining){
                    take = (curr[remaining - coins[ind]]);
                }
                curr[remaining] = (1ll*take + notTake);
            }
            prev = curr;
        }
        return prev[amount];
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int change(int amount, const vector<int>& coins) {
        // dp[a] = number of ways to make amount a using processed coins
        vector<long long> dp(amount + 1, 0);
        dp[0] = 1;                         // empty combination

        for (int c : coins) {              // outer loop: each coin
            for (int a = c; a <= amount; ++a) { // inner loop: forward scan
                dp[a] += dp[a - c];        // add ways that end with coin c
            }
        }
        return static_cast<int>(dp[amount]); // guaranteed to fit in 32‑bit
    }
};
```

**Explanation of refinements**

- Replaced the two‑array (`prev`/`curr`) scheme with a single `dp` vector, exploiting the forward inner loop to allow unlimited reuse of the current coin.  
- Used `const vector<int>&` for the input to avoid unnecessary copies.  
- Added clear comments describing the meaning of `dp[a]`.  
- Cast the final `long long` result back to `int`, matching the problem’s guarantee.  

## Code Walkthrough

- `dp[0] = 1` seeds the DP: there is exactly one way (choose nothing) to reach amount 0.  
- For each coin `c`, the inner loop starts at `a = c`.  
  - `dp[a] += dp[a - c]` takes **all** ways that already form `a - c` (using this coin and any previous ones) and extends each of them by one additional `c`.  
  - Because we iterate `a` **ascending**, the updated `dp[a - c]` may itself have been increased earlier in the same outer iteration, which correctly models the *unbounded* nature of the coin.  
- After processing every coin, `dp[amount]` holds the total number of distinct unordered combinations.
