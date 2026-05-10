# 45. Jump Game II

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Dynamic Programming, Greedy &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 20.6 MB

---

## Problem

You are given a **0-indexed** array of integers `nums` of length `n`. You are initially positioned at index 0.

Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at index `i`, you can jump to any index `(i + j)` where:

	
- `0 <= j <= nums[i]` and
	
- `i + j < n`

Return _the minimum number of jumps to reach index _`n - 1`. The test cases are generated such that you can reach index `n - 1`.

 

**Example 1:**

> **Input:** nums = [2,3,1,1,4]
> **Output:** 2
> **Explanation:** The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

**Example 2:**

> **Input:** nums = [2,3,0,1,4]
> **Output:** 2

## Constraints

- `1 <= nums.length <= 104`
	
- `0 <= nums[i] <= 1000`
	
- It's guaranteed that you can reach `nums[n - 1]`.

## Hints

_No hints provided._

---

## Intuition

The array can be seen as a **layered BFS** where each layer contains all indices reachable with the same number of jumps.  
The “aha” moment is to **grow the current layer greedily**: while we are inside the current jump’s reach, we look ahead to the farthest index any of those positions can push us to. Once we exhaust the current layer, we must take another jump and set the new layer’s boundary to that farthest reach. This single‑pass greedy expansion yields the optimal (minimum) number of jumps.

## Approach

1. **Edge case** – if `n == 1` return `0` (already at the last index).  
2. Initialise  
   * `jumps = 0` – number of jumps taken so far,  
   * `currentEnd = 0` – rightmost index reachable with `jumps` jumps,  
   * `farthest = 0` – farthest index reachable from any index within the current layer.  
3. Iterate `i` from `0` to `n‑2` (we never need to jump from the last index):  
   * Update `farthest = max(farthest, i + nums[i])`.  
   * When `i == currentEnd` we have exhausted the current layer:  
     * Increment `jumps`.  
     * Set `currentEnd = farthest` (the next layer’s boundary).  
4. Return `jumps`.

## Complexity Analysis

|                | Complexity | Reason                                            |
|----------------|------------|---------------------------------------------------|
| **Time**       | $O(n)$     | Single linear scan; each index processed once.   |
| **Space**      | $O(1)$     | Only a few integer variables regardless of $n$.   |

## Key Takeaways

- **Greedy layer expansion** mirrors BFS on an implicit graph, guaranteeing optimality without explicit queue storage.  
- Tracking only the **farthest reachable index** inside the current window eliminates the $O(n^2)$ DP formulation.  
- The condition `i == currentEnd` is the precise moment when a new jump is unavoidable; it converts a continuous scan into discrete jump counts.  
- Handling `n == 1` separately prevents an off‑by‑one error, because the loop would otherwise increment `jumps` unnecessarily.

## My Original Solution

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int jumpCount = 1;
        if(nums.size() == 1) return 0;
        int low = 0, high = nums[0];
        int n = nums.size();
        while(high < n - 1){
            int farthest = high;
            for(int i = low;i <= high;i++){
                farthest = max(farthest, nums[i] + i);
            }
            low = high + 1;
            high = farthest;
            jumpCount++;
        }
        return jumpCount;
    }
};
```

## Professional Refactor

```cpp
// 45. Jump Game II – Greedy O(n) solution
class Solution {
public:
    int jump(const vector<int>& nums) {
        const int n = nums.size();
        if (n == 1) return 0;                 // already at the end

        int jumps = 0;                         // number of jumps performed
        int currentEnd = 0;                    // farthest index reachable with 'jumps' jumps
        int farthest = 0;                      // farthest index reachable from the current layer

        // we never need to consider the last index as a starting point
        for (int i = 0; i < n - 1; ++i) {
            farthest = max(farthest, i + nums[i]); // best reach from any i in current layer

            // when we reach the end of the current layer, we must jump
            if (i == currentEnd) {
                ++jumps;
                currentEnd = farthest;         // set boundary for the next layer
            }
        }
        return jumps;
    }
};
```

## Code Walkthrough

- **`farthest = max(farthest, i + nums[i])`**  
  Extends the reachable horizon by considering the jump length from the current index `i`.  

- **`if (i == currentEnd)`**  
  Signals that all positions reachable with the current number of jumps have been examined; a new jump is mandatory.  

- **`currentEnd = farthest`**  
  Moves the window boundary to the farthest index discovered, effectively starting the next BFS layer.  

The loop runs once over the array, and each update maintains the invariant that `currentEnd` always marks the rightmost index reachable with `jumps` jumps, ensuring the final `jumps` count is minimal.
