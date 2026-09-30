# 1111. Maximum Nesting Depth of Two Valid Parentheses Strings

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** String, Stack, Bracket Sequences &nbsp;|&nbsp; **Solved:** September 30, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 10121.1 MB

---

## Problem

A string is a _valid parentheses string_ (denoted VPS) if and only if it consists of `"("` and `")"` characters only, and:

	
- It is the empty string, or
	
- It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are VPS's, or
	
- It can be written as `(A)`, where `A` is a VPS.

We can similarly define the _nesting depth_ `depth(S)` of any VPS `S` as follows:

	
- `depth("") = 0`
	
- `depth(A + B) = max(depth(A), depth(B))`, where `A` and `B` are VPS's
	
- `depth("(" + A + ")") = 1 + depth(A)`, where `A` is a VPS.

For example, `""`, `"()()"`, and `"()(()())"` are VPS's (with nesting depths 0, 1, and 2), and `")("` and `"(()"` are not VPS's.

Given a VPS seq, split it into two disjoint subsequences `A` and `B`, such that `A` and `B` are VPS's (and `A.length + B.length = seq.length`). The subsequences may not necessarily be contiguous.

For example, for the sequence `123456789`, one possible split is:

	
- 
	
`A = {1, 3, 5, 7, 9}`,

	
	
- 
	
`B = {2, 4, 6, 8}`.

	

This corresponds to the output `[0, 1, 0, 1, 0, 1, 0, 1, 0]`  where 0 indicates membership in `A` and 1 indicates membership in `B`.

Now choose **any** such `A` and `B` such that `max(depth(A), depth(B))` is the minimum possible value.

Return an `answer` array (of length `seq.length`) that encodes such a choice of `A` and `B`:  `answer[i] = 0` if `seq[i]` is part of `A`, else `answer[i] = 1`.  Note that even though multiple answers may exist, you may return any of them.

 

**Example 1:**

> **Input:** seq = "(()())"
> **Output:** [0,1,1,1,1,0]

**Example 2:**

> **Input:** seq = "()(())()"
> **Output:** [0,0,0,1,1,0,1,1]

## Constraints

- `1 <= seq.size <= 10000`

## Hints

_No hints provided._

---

## Intuition

The nesting depth of a VPS is built by **adding 1** for every opening parenthesis that is currently “active”.  
If we can keep the *active* depths of the two subsequences as balanced as possible, the larger of the two depths will be minimized.  
Thus, at each `'('` we should give it to the group whose current depth is **smaller**, and at each `')'` we must close the most‑recent `'('` of the same group – which is exactly the group that now has the larger depth.  
This greedy balancing is equivalent to assigning parentheses according to the **parity of the overall nesting depth** (`depth % 2`). The result’s maximal depth is $\lceil\text{originalDepth}/2\rceil$, which is provably optimal.

---

## Approach

1. Initialise two counters `depthA` and `depthB` to 0 – they store the current nesting depth of groups A and B.  
2. Scan the string `seq` from left to right.  
   * If the character is `'('`  
     * Choose the group with the smaller current depth (`depthA <= depthB ? A : B`).  
     * Record the choice (`0` for A, `1` for B) and increment the chosen group’s depth.  
   * If the character is `')'`  
     * The matching `'('` must belong to the group that currently has the **larger** depth, because that group opened more parentheses that are still unclosed.  
     * Record the opposite group index and decrement its depth.  
3. Return the built answer array.

The algorithm never needs an explicit stack; the two depth counters implicitly encode the stack tops of the two subsequences.

---

## Complexity Analysis

|                | Complexity | Reason                                    |
|----------------|------------|-------------------------------------------|
| **Time**       | $O(n)$     | Single pass over the $n$ characters.      |
| **Space**      | $O(n)$     | Output array of length $n$ (no extra data).|

---

## Key Takeaways

- **Greedy depth balancing** yields the optimal split: always assign a parenthesis to the group with the smaller current nesting depth.  
- The solution is **equivalent to using parity** (`depth % 2`) of the global nesting depth, which eliminates the need for any explicit stack.  
- The minimal possible maximal depth after split is $\lceil D/2\rceil$, where $D$ is the depth of the original VPS.  
- Maintaining only two integer counters is sufficient; this reduces both code complexity and constant‑factor overhead.

---

## My Original Solution

```cpp
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        vector<int> res(n, -1);
        int a = 0, b = 0;
        for(int i = 0;i < n;i++){
            if(seq[i] == '('){
                if(a < b){
                    res[i] = 0;
                    a++;
                }else{
                    res[i] = 1;
                    b++;
                }
            }else{
                if(a < b){
                    res[i] = 1;
                    b--;
                }else{
                    res[i] = 0;
                    a--;
                }
            }
        }
        return res;
    }
};
```

## Professional Refactor

```cpp
// 1111. Maximum Nesting Depth of Two Valid Parentheses Strings
// Time  : O(n)
// Space : O(n) – answer array
class Solution {
public:
    vector<int> maxDepthAfterSplit(const string& seq) {
        const int n = static_cast<int>(seq.size());
        vector<int> ans(n);
        int depthA = 0; // current depth of subsequence A (label 0)
        int depthB = 0; // current depth of subsequence B (label 1)

        for (int i = 0; i < n; ++i) {
            if (seq[i] == '(') {
                // open a new level in the shallower subsequence
                if (depthA <= depthB) {
                    ans[i] = 0;
                    ++depthA;
                } else {
                    ans[i] = 1;
                    ++depthB;
                }
            } else { // ')'
                // close the level that was opened last (the deeper subsequence)
                if (depthA <= depthB) {
                    ans[i] = 1;
                    --depthB;
                } else {
                    ans[i] = 0;
                    --depthA;
                }
            }
        }
        return ans;
    }
};
```

## Code Walkthrough

- **`depthA` / `depthB`**: act as the top of an implicit stack for each subsequence; they store how many `'('` are currently unmatched in that group.  
- **Opening `'('`**: we pick the group with the *smaller* depth (`depthA <= depthB`). This keeps the two depths as balanced as possible, directly minimizing the eventual `max(depthA, depthB)`.  
- **Closing `')'`**: the matching `'('` must belong to the group that currently has the *larger* depth, because that group opened more unmatched `'('`. Hence we assign the closing parenthesis to the opposite label and decrement that group’s depth.  
- The loop processes each character once, building the answer array on‑the‑fly; no extra data structures are required.
