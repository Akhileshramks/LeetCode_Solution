# 788. Rotated Digits

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Math, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 2, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 8.5 MB

---

## Problem

An integer `x` is a **good** if after rotating each digit individually by 180 degrees, we get a valid number that is different from `x`. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

	
- `0`, `1`, and `8` rotate to themselves,
	
- `2` and `5` rotate to each other (in this case they are rotated in a different direction, in other words, `2` or `5` gets mirrored),
	
- `6` and `9` rotate to each other, and
	
- the rest of the numbers do not rotate to any other number and become invalid.

Given an integer `n`, return _the number of **good** integers in the range _`[1, n]`.

 

**Example 1:**

> **Input:** n = 10
> **Output:** 4
> **Explanation:** There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
> Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.

**Example 2:**

> **Input:** n = 1
> **Output:** 0

**Example 3:**

> **Input:** n = 2
> **Output:** 1

## Constraints

- `1 <= n <= 104`

## Hints

_No hints provided._

---

## Intuition

The problem asks for a count of numbers whose **digit‑wise rotation** stays a valid digit **and** changes the overall value.  
The only way to guarantee the “different from original” condition is to ensure that **at least one digit belongs to the set** $\{2,5,6,9\}$, because the other rotatable digits $\{0,1,8\}$ map to themselves.  
Thus the task reduces to “how many numbers $\le n$ consist only of the allowed digits $\{0,1,2,5,6,8,9\}$ and contain at least one “changing” digit”.  
Counting numbers with digit constraints up to a bound is a classic **digit DP** scenario: we process the decimal string of $n$ from most to least significant, keep a *tight* flag that tells whether the prefix is already smaller than the bound, and a *hasChange* flag that records whether a changing digit has appeared. The DP state $(\text{pos},\text{tight},\text{hasChange})$ captures exactly the information needed for optimal sub‑structure.

## Approach

1. **Pre‑process** a boolean array `valid[10]` marking digits that survive rotation (`1` for $\{0,1,2,5,6,8,9\}$, `0` otherwise).  
2. Convert $n$ to its decimal string `s`.  
3. Define a memoized recursive function `dfs(pos, tight, hasChange)` returning the count of good numbers for the suffix starting at index `pos`.  
   - **Base case**: when `pos == s.length()`, return `1` if `hasChange` is true (a valid good number), else `0`.  
   - **Transition**:  
     - `limit = tight ? s[pos] - '0' : 9`.  
     - Iterate `d` from `0` to `limit`. Skip `d` if `valid[d] == 0`.  
     - `newHasChange = hasChange || (d==2||d==5||d==6||d==9)`.  
     - `newTight = tight && (d == limit)`.  
     - Accumulate `dfs(pos+1, newTight, newHasChange)`.  
4. Store results in a 3‑dimensional DP table `dp[pos][tight][hasChange]` initialized to `-1`.  
5. Call `dfs(0, true, false)` and return the result.

## Complexity Analysis

|                | Complexity | Reason                                                            |
|----------------|------------|-------------------------------------------------------------------|
| **Time**       | $O(L \times 2 \times 2 \times 10)$ = $O(L)$ | $L = \text{len}(n)$; each state explores at most 10 digits. |
| **Space**      | $O(L \times 2 \times 2)$ = $O(L)$ | DP table stores one integer per state.                           |

Since $n \le 10^4$, $L \le 5$, so the algorithm runs essentially in constant time.

## Key Takeaways

- **Digit DP** is the go‑to technique for counting numbers with per‑digit constraints under an upper bound.  
- Introducing a **“hasChange” flag** isolates the “different after rotation” requirement without complicating the transition logic.  
- Using a **valid‑digit mask** (`valid[10]`) lets us prune illegal branches early, keeping the DP tight and memory‑light.  
- The **tight flag** (`tight`) elegantly handles the “≤ n” condition by limiting the digit range only when the prefix matches the bound.

## My Original Solution

```cpp
class Solution {
public:
    vector<int> isValid = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1};
    int findDigitSum(int ind, int tight, string s, int isPresent, vector<vector<vector<int>>>& dp){
        if(ind == s.size()){
            if(!isPresent) return 0;
            return 1;
        }
        if(dp[ind][tight][isPresent] != -1) return dp[ind][tight][isPresent];
        int limit = tight ? s[ind] - '0' : 9;
        int ans = 0;
        for(int i = 0;i <= limit;i++){
            if(!isValid[i]) continue;
            int new_isPresent = isPresent | (i == 2 || i == 5 || i == 6 || i == 9);
            int new_tight = (tight & (s[ind] - '0' == i)) ? tight : 0;
            ans += findDigitSum(ind + 1, new_tight, s, new_isPresent, dp);
        }
        return dp[ind][tight][isPresent] = ans;
    }
    int rotatedDigits(int n) {
        string s = to_string(n);
        vector<vector<vector<int>>> dp(s.size() , vector<vector<int>>(2, vector<int>(2, -1)));
        return findDigitSum(0, 1, s, 0, dp);
    }
};
```

## Professional Refactor

```cpp
// rotated_digits.cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
    // digits that stay valid after a 180° rotation
    const array<int,10> valid = {1,1,1,0,0,1,1,0,1,1};
    // memo[pos][tight][hasChange] = -1 means uncomputed
    vector<vector<array<int,2>>> memo;
    string bound;

    int dfs(int pos, bool tight, bool hasChange) {
        if (pos == (int)bound.size())
            return hasChange ? 1 : 0;               // count only if a changing digit appeared

        int &res = memo[pos][tight][hasChange];
        if (res != -1) return res;
        res = 0;

        int limit = tight ? bound[pos] - '0' : 9;
        for (int d = 0; d <= limit; ++d) {
            if (!valid[d]) continue;                // skip illegal digits
            bool newHasChange = hasChange || (d==2 || d==5 || d==6 || d==9);
            bool newTight = tight && (d == limit);
            res += dfs(pos + 1, newTight, newHasChange);
        }
        return res;
    }

public:
    int rotatedDigits(int n) {
        bound = to_string(n);
        int len = bound.size();
        memo.assign(len, vector<array<int,2>>(2, array<int,2>{-1,-1}));
        return dfs(0, true, false);
    }
};
```

## Code Walkthrough

- **`valid` array**: constant lookup to discard digits `3,4,7` instantly.  
- **`memo`**: a 3‑dimensional table flattened to `vector<vector<array<int,2>>>` for cache‑friendly access; each entry stores results for both `hasChange` states.  
- **Base case (`pos == bound.size()`)**: returns `1` only when `hasChange` is true, guaranteeing the rotated number differs from the original.  
- **`limit` computation**: respects the tight constraint; when `tight` is `false` we may use any digit `0‑9`.  
- **Transition loop**: skips invalid digits, updates `newHasChange` with a bitwise‑or‑like expression, and propagates the tight flag only when the chosen digit equals the current bound digit.  
- **Result aggregation**: the sum of recursive calls yields the count of good numbers for the current prefix.  

The refactored version keeps the same $O(L)$ time/space complexity while improving readability and cache locality.
