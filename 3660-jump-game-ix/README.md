# 3660. Jump Game IX

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming &nbsp;|&nbsp; **Solved:** May 7, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 28 ms &nbsp;|&nbsp; **Memory:** 219 MB

---

## Problem

You are given an integer array `nums`.

From any index `i`, you can jump to another index `j` under the following rules:

	
- Jump to index `j` where `j > i` is allowed only if `nums[j] < nums[i]`.
	
- Jump to index `j` where `j < i` is allowed only if `nums[j] > nums[i]`.

For each index `i`, find the **maximum** **value** in `nums` that can be reached by following **any** sequence of valid jumps starting at `i`.

Return an array `ans` where `ans[i]` is the **maximum** **value** reachable starting from index `i`.

 

**Example 1:**

**Input:** nums = [2,1,3]

**Output:** [2,2,3]

**Explanation:**

	
- For `i = 0`: No jump increases the value.
	
- For `i = 1`: Jump to `j = 0` as `nums[j] = 2` is greater than `nums[i]`.
	
- For `i = 2`: Since `nums[2] = 3` is the maximum value in `nums`, no jump increases the value.

Thus, `ans = [2, 2, 3]`.

**Example 2:**

**Input:** nums = [2,3,1]

**Output:** [3,3,3]

**Explanation:**

	
- For `i = 0`: Jump forward to `j = 2` as `nums[j] = 1` is less than `nums[i] = 2`, then from `i = 2` jump to `j = 1` as `nums[j] = 3` is greater than `nums[2]`.
	
- For `i = 1`: Since `nums[1] = 3` is the maximum value in `nums`, no jump increases the value.
	
- For `i = 2`: Jump to `j = 1` as `nums[j] = 3` is greater than `nums[2] = 1`.

Thus, `ans = [3, 3, 3]`.

## Constraints

- `1 <= nums.length <= 105`
	
- `1 <= nums[i] <= 109​​​​​​​`

## Hints

1. Think of the array as a directed graph where edges represent valid jumps.
2. From index `i`, forward jumps go only to smaller values; backward jumps go only to larger values.
3. The maximum reachable value from `i` is the maximum value in the connected component reachable under these jump rules.
4. You can find connected ranges by looking at prefix maximums and suffix minimums, a cut happens where all values to the left are <= all values to the right.

---

## Intuition

The jump rules force every valid move to **strictly decrease** when we go right and **strictly increase** when we go left.  
Consequently, once we step onto a smaller element while scanning from left to right, we can never leave the block of indices that are bounded on the left by the first larger element and on the right by the first smaller element.  
All indices inside such a block can reach each other, and the **largest value reachable from any index in the block is simply the maximum element of the block**.  

Thus the problem reduces to **partitioning the array into contiguous blocks where the maximum value is the answer for every position inside the block**.  
A decreasing **monotonic stack** naturally discovers those blocks: whenever a new element `nums[i]` is smaller than the stack top, the top can no longer jump rightward past `i`, so it belongs to the same block as `i`. By popping and merging intervals we propagate the block’s maximum.

---

## Approach

1. Initialise an empty stack. Each stack entry stores  
   * `val` – the current maximum of the block,  
   * `l`   – leftmost index of the block,  
   * `r`   – rightmost index (initially the element’s own index).  

2. Scan `nums` from left to right (`i = 0 … n‑1`):
   * Create a new block `{val = nums[i], l = i, r = i}`.
   * While the stack is non‑empty **and** `stack.top.val > nums[i]` (i.e. the top block cannot jump right past `i`):
     * Pop the top block `k`.
     * Merge it into the new block:  
       `new.val = max(new.val, k.val)`  
       `new.l   = k.l` (the leftmost boundary expands leftwards).
   * Push the merged block back onto the stack.

3. After the scan the stack holds disjoint blocks in increasing order of `val`.  
   Pop each block and fill `ans[l … r]` with its stored `val`.

4. Return `ans`.

---

## Complexity Analysis

|            | Complexity | Reason                                                                 |
|------------|------------|------------------------------------------------------------------------|
| **Time**   | $O(n)$     | Each index is pushed once and popped at most once from the stack.    |
| **Space**  | $O(n)$     | The stack may hold up to $n$ blocks in the worst case (strictly decreasing array). |

---

## Key Takeaways

* **Direction‑dependent monotonicity** turns a seemingly global reachability problem into a local interval‑merging problem.  
* A **decreasing monotonic stack** can simultaneously track the left boundary of a component and its maximum value, enabling $O(n)$ processing.  
* The answer for every index is **the maximum of its component**, not a result of a multi‑step DP; recognizing this eliminates the need for explicit graph traversal.  
* Merging intervals while maintaining the current maximum avoids any extra passes or segment‑tree queries.

---

## My Original Solution

```cpp
class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        stack<pair<int, pair<int,int>>> st;
        for(int i = 0;i < n;i++){
            pair<int, pair<int,int>> newElem = {nums[i], {i, i}};
            while(!st.empty() && st.top().first > nums[i]){
                auto k = st.top();
                st.pop();
                newElem.first = max(newElem.first, k.first);
                newElem.second.first = k.second.first;
            }
            st.push(newElem);
        }
        while(!st.empty()){
            auto k = st.top();
            st.pop();
            for(int j = k.second.first;j <= k.second.second;j++) res[j] = k.first;
        }
        return res;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        const int n = nums.size();
        vector<int> ans(n);
        struct Block {
            int maxVal;   // maximum value inside the block
            int left;     // leftmost index of the block
            int right;    // rightmost index (inclusive)
        };
        stack<Block> st;

        for (int i = 0; i < n; ++i) {
            Block cur{nums[i], i, i};

            // Merge all previous blocks that cannot jump past i
            while (!st.empty() && st.top().maxVal > nums[i]) {
                const Block top = st.top(); st.pop();
                cur.maxVal = max(cur.maxVal, top.maxVal);
                cur.left   = top.left;               // expand left boundary
            }
            st.push(cur);
        }

        // Unwind the stack and write answers for each block
        while (!st.empty()) {
            const Block blk = st.top(); st.pop();
            for (int idx = blk.left; idx <= blk.right; ++idx) {
                ans[idx] = blk.maxVal;
            }
        }
        return ans;
    }
};
```

## Code Walkthrough

* **Block definition** – bundles the needed information (`maxVal`, `left`, `right`) so the stack manipulations stay readable.  
* **Merging loop** (`while (!st.empty() && st.top().maxVal > nums[i])`):  
  * The condition captures the exact situation where the top block cannot move rightward beyond the current index because its maximum is larger than `nums[i]`.  
  * Popping merges the interval: the new block inherits the larger maximum and the leftmost boundary of the popped block.  
* **Final unwind** – each remaining block is independent; filling `ans[left … right]` with `maxVal` yields the required maximum reachable value for every position.
