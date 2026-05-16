# 154. Find Minimum in Rotated Sorted Array II

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Binary Search &nbsp;|&nbsp; **Solved:** May 16, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 15609.4 MB

---

## Problem

Suppose an array of length `n` sorted in ascending order is **rotated** between `1` and `n` times. For example, the array `nums = [0,1,4,4,5,6,7]` might become:

	
- `[4,5,6,7,0,1,4]` if it was rotated `4` times.
	
- `[0,1,4,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` that may contain **duplicates**, return _the minimum element of this array_.

You must decrease the overall operation steps as much as possible.

 

**Example 1:**

> **Input:** nums = [1,3,5]
> **Output:** 1

**Example 2:**

> **Input:** nums = [2,2,2,0,1]
> **Output:** 0

## Constraints

- `n == nums.length`
	
- `1 <= n <= 5000`
	
- `-5000 <= nums[i] <= 5000`
	
- `nums` is sorted and rotated between `1` and `n` times.

 

**Follow up:** This problem is similar to Find Minimum in Rotated Sorted Array, but `nums` may contain **duplicates**. Would this affect the runtime complexity? How and why?

## Hints

_No hints provided._

---

## Intuition

The minimum is the only element that is **not greater** than any element to its right. In a rotated sorted array the rightmost part is always sorted, so by comparing the middle element with the rightmost element we can decide which side *must* contain the minimum.  
When `nums[mid] > nums[high]` the minimum lies strictly to the right of `mid`.  
When `nums[mid] < nums[high]` the minimum is at `mid` or to its left.  
If they are equal, duplicates mask the ordering; the only safe move is to shrink the search interval by discarding `high` (which cannot be the unique minimum because it equals `mid`). This observation lets us keep the binary‑search framework while handling duplicates.

## Approach

1. Initialise pointers `low = 0` and `high = n‑1`.  
2. While `low < high`  
   1. Compute `mid = low + (high‑low)/2` (prevents overflow).  
   2. **Case 1:** `nums[mid] > nums[high]` → minimum is right of `mid`; set `low = mid + 1`.  
   2. **Case 2:** `nums[mid] < nums[high]` → minimum is at `mid` or left; set `high = mid`.  
   3. **Case 3:** `nums[mid] == nums[high]` → duplicate ambiguity; safely reduce interval with `high--`.  
3. When the loop ends, `low == high` and points to the smallest element; return `nums[low]`.

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(\log n)$ (average) | Each iteration discards roughly half of the interval. |
| **Time** (worst) | $O(n)$ | When many duplicates cause repeated `high--`, we may scan linearly. |
| **Space**      | $O(1)$     | Only a few integer pointers are used.                                 |

## Key Takeaways

- **Compare with `high` instead of `low`**: `nums[mid]` vs `nums[high]` reliably indicates which side is unsorted, even when the rotation point is near the left end.  
- **Equality case requires linear fallback**: Duplicates break the strict ordering; the only safe operation is `high--`, which degrades to $O(n)$ but preserves correctness.  
- **Midpoint calculation must avoid overflow**: `mid = low + (high‑low)/2` works for any integer range.  
- **Binary search still applies**: Despite duplicates, the algorithm retains the binary‑search skeleton, yielding $O(\log n)$ on typical inputs.

## My Original Solution

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int res = INT_MAX;
        int n = nums.size();
        int low = 0, high = n - 1;
        while(low < high){
            int mid = low + (high - low) / 2;
            if(nums[mid] > nums[high]){
                low = mid + 1;
            }else if(nums[mid] < nums[high]){
                high = mid;
            }else{
                high--;
            }
        }
        return nums[low];
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int findMin(const vector<int>& nums) {
        int low = 0;
        int high = static_cast<int>(nums.size()) - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high]) {
                // Minimum must be right of mid
                low = mid + 1;
            } else if (nums[mid] < nums[high]) {
                // Minimum is at mid or left of it
                high = mid;
            } else {
                // Duplicate: cannot decide, safely shrink interval
                --high;
            }
        }
        return nums[low];
    }
};
```

## Code Walkthrough

- **`while (low < high)`** – loop continues until the search window collapses to a single index, which will be the minimum.  
- **`mid = low + (high - low) / 2`** – avoids overflow that could happen with `(low + high) / 2`.  
- **`if (nums[mid] > nums[high])`** – the right half is strictly increasing, so the pivot (minimum) must be to the right of `mid`; move `low` past `mid`.  
- **`else if (nums[mid] < nums[high])`** – `mid` is on the unsorted side or is the pivot; shrink the window to `[low, mid]`.  
- **`else`** – `nums[mid] == nums[high]`; duplicates hide the ordering, but `nums[high]` cannot be the unique minimum because it equals `mid`, so we safely discard it with `--high`.  
- **`return nums[low];`** – after convergence, `low` (or `high`) indexes the smallest element.
