# 3975. Filter Occupied Intervals

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Sorting &nbsp;|&nbsp; **Solved:** June 30, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 118 ms &nbsp;|&nbsp; **Memory:** 190500.0 MB

---

## Problem

You are given a 2D integer array `occupiedIntervals`, where `occupiedIntervals[i] = [starti, endi]` represents a time interval during which you are occupied. Each interval starts at `starti` and ends at `endi`, **inclusive**. These intervals may **overlap**.

You are also given two integers `freeStart` and `freeEnd`, which define a free time interval from `freeStart` to `freeEnd`, inclusive.

Your task is to merge **all** occupied intervals that overlap or touch, then remove **all** integer points in the free interval from the merged occupied intervals.

Two intervals touch if the second interval starts **immediately after** the first one ends. For example, `[1, 1]` and `[2, 2]` touch and should be merged into `[1, 2]`.

Return the **remaining** occupied intervals in **sorted** order. The returned intervals must be **non-overlapping** and must contain the **minimum** number of intervals possible. If there are no remaining occupied points, return an empty list.

 

**Example 1:**

**Input:** occupiedIntervals = [[2,6],[4,8],[10,10],[10,12],[14,16]], freeStart = 7, freeEnd = 11

**Output:** [[2,6],[12,12],[14,16]]

**Explanation:**

	
- After merging, the occupied intervals are `[2, 8]`, `[10, 12]`, and `[14, 16]`.
	
- Excluding the free interval `[7, 11]` results in `[2, 6]`, `[12, 12]`, and `[14, 16]`.

**Example 2:**

**Input:** occupiedIntervals = [[1,5],[2,3]], freeStart = 3, freeEnd = 8

**Output:** [[1,2]]

**Explanation:**

	
- After merging, the occupied interval is `[1, 5]`.
	
- Excluding the free interval `[3, 8]` results in `[1, 2]`.

## Constraints

- `1 <= occupiedIntervals.length <= 5 * 104`
	
- `occupiedIntervals[i].length == 2`
	
- `1 <= starti <= endi <= 109`
	
- `1 <= freeStart <= freeEnd <= 109`

## Hints

1. Sort the occupied intervals by start time.
2. While merging, two intervals should be combined if the next interval starts at most one point after the current interval ends.
3. After merging, remove `[freeStart, freeEnd]` from each merged interval independently.
4. An interval may disappear completely, shrink on one side, remain unchanged, or split into two intervals.

---

## Intuition

The "Aha!" moment in this problem is recognizing that we can first merge all overlapping intervals and then remove the free interval from the merged intervals. This is made possible by the fact that the intervals are given as start and end points, allowing us to easily compare and merge them. The key insight is to understand that two intervals can be merged if the start of the second interval is less than or equal to the end of the first interval plus one, which means they either overlap or touch.

## Approach

1. First, we sort the occupied intervals based on their start times. This is necessary to ensure that we can merge overlapping intervals in a single pass.
2. We then initialize our result with the first interval and iterate over the rest of the intervals. For each interval, we check if it can be merged with the last interval in our result. If it can, we update the end time of the last interval. If not, we add the current interval to our result.
3. After merging all overlapping intervals, we iterate over our result and remove the free interval from each merged interval. If a merged interval is completely contained within the free interval, we skip it. If a merged interval overlaps with the free interval, we split it into two intervals: one before the free interval and one after.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n \log n)$ | The time complexity comes from sorting the occupied intervals, where $n$ is the number of intervals. The subsequent for loops iterate over the intervals, resulting in a linear time complexity of $O(n)$. However, the sorting operation dominates the overall time complexity. |
| **Space** | $O(n)$ | The space complexity comes from storing the merged intervals in our result, where in the worst case, we might need to store all intervals if none of them overlap. |

## Key Takeaways

* The key to solving this problem efficiently is recognizing that sorting the intervals by their start times allows us to merge overlapping intervals in a single pass.
* Understanding how to compare and merge intervals based on their start and end times is crucial for the solution.
* The problem requires careful handling of edge cases, such as when a merged interval is partially or completely contained within the free interval.
* The solution demonstrates how to apply a two-step approach: first, simplify the problem by merging overlapping intervals, and then apply the main operation (removing the free interval) to the simplified data.

## My Original Solution

```cpp
class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {
        vector<vector<int>> res;
        sort(occupiedIntervals.begin(), occupiedIntervals.end());
        res.push_back(occupiedIntervals[0]);
        int n = occupiedIntervals.size();
        for(int i = 1;i < n;i++){
            vector<int>& last = res.back();
            vector<int>& curr = occupiedIntervals[i];

            if(curr[0] <= last[1] + 1) last[1] = max(last[1], curr[1]);
            else res.push_back(curr);
        }

        vector<vector<int>> finalRes;
        for(auto curr : res){
            int l = curr[0];
            int r = curr[1];

            if(r < freeStart || l > freeEnd){
                finalRes.push_back(curr);
                continue;
            }

            if(l < freeStart){
                finalRes.push_back({l, freeStart - 1});
            }

            if(r > freeEnd){
                finalRes.push_back({freeEnd + 1, r});
            }
        }
        return finalRes;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {
        // Sort the intervals by their start times
        sort(occupiedIntervals.begin(), occupiedIntervals.end());
        
        // Initialize the result with the first interval
        vector<vector<int>> mergedIntervals = {occupiedIntervals[0]};
        
        // Merge overlapping intervals
        for (int i = 1; i < occupiedIntervals.size(); ++i) {
            auto& lastMerged = mergedIntervals.back();
            auto& current = occupiedIntervals[i];
            
            if (current[0] <= lastMerged[1] + 1) {
                // Update the end time of the last merged interval if necessary
                lastMerged[1] = max(lastMerged[1], current[1]);
            } else {
                // Add the current interval to the merged intervals if it cannot be merged
                mergedIntervals.push_back(current);
            }
        }
        
        // Remove the free interval from the merged intervals
        vector<vector<int>> result;
        for (auto& interval : mergedIntervals) {
            int start = interval[0];
            int end = interval[1];
            
            if (end < freeStart || start > freeEnd) {
                result.push_back(interval);
                continue;
            }
            
            if (start < freeStart) {
                result.push_back({start, freeStart - 1});
            }
            
            if (end > freeEnd) {
                result.push_back({freeEnd + 1, end});
            }
        }
        
        return result;
    }
};
```

## Code Walkthrough

The core transformation in this algorithm is the merging of overlapping intervals and the subsequent removal of the free interval. The key steps are:

* Sorting the intervals by their start times to enable efficient merging.
* Iterating over the sorted intervals and merging overlapping intervals by updating the end time of the last merged interval.
* Removing the free interval from the merged intervals by splitting intervals that overlap with the free interval into two separate intervals.
