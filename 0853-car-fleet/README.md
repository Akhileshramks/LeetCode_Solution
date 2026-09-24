# 853. Car Fleet

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Stack, Sorting, Monotonic Stack &nbsp;|&nbsp; **Solved:** September 24, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 58 ms &nbsp;|&nbsp; **Memory:** 113738.3 MB

---

## Problem

There are `n` cars at given miles away from the starting mile 0, traveling to reach the mile `target`.

You are given two integer arrays `position` and `speed`, both of length `n`, where `position[i]` is the starting mile of the `ith` car and `speed[i]` is the speed of the `ith` car in miles per hour.

A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.

A **car fleet** is a single car or a group of cars driving next to each other. The speed of the car fleet is the **minimum** speed of any car in the fleet.

If a car catches up to a car fleet at the mile `target`, it will still be considered as part of the car fleet.

Return the number of car fleets that will arrive at the destination.

 

**Example 1:**

**Input:** target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]

**Output:** 3

**Explanation:**

	
- The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12. The fleet forms at `target`.
	
- The car starting at 0 (speed 1) does not catch up to any other car, so it is a fleet by itself.
	
- The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches `target`.

**Example 2:**

**Input:** target = 10, position = [3], speed = [3]

**Output:** 1

**Explanation:**

There is only one car, hence there is only one fleet.

**Example 3:**

**Input:** target = 100, position = [0,2,4], speed = [4,2,1]

**Output:** 1

**Explanation:**

	
- The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting each other at 4. The car starting at 4 (speed 1) travels to 5.
	
- Then, the fleet at 4 (speed 2) and the car at position 5 (speed 1) become one fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches `target`.

## Constraints

- `n == position.length == speed.length`
	
- `1 <= n <= 105`
	
- `0 < target <= 106`
	
- `0 <= position[i] < target`
	
- All the values of `position` are **unique**.
	
- `0 < speed[i] <= 106`

## Hints

_No hints provided._

---

## Intuition

The only thing that matters for a car to catch up with another is **when** it would reach the destination, not the exact path it follows.  
If we compute the arrival time  

\[
t_i = \frac{\text{target} - \text{position}_i}{\text{speed}_i}
\]

for every car, the problem becomes: *given cars ordered by their starting positions, how many distinct “latest” times appear when we scan from the car closest to the target towards the start?*  

A car can only join a fleet that is **slower** (i.e., has a **larger** arrival time) than itself. Thus, while scanning from right‑most to left‑most car, we keep the smallest arrival time seen so far; any car with a larger time starts a new fleet. This greedy, monotonic‑stack‑like observation is the “Aha!” moment.

---

## Approach

1. **Compute arrival times**  
   For each index `i`, calculate `time[i] = (target - position[i]) / speed[i]` as a `double`.

2. **Sort by starting position**  
   Pair each `position[i]` with its `time[i]` and sort the pairs in **descending** order of `position` (i.e., from the car nearest to the target to the farthest).

3. **Traverse and count fleets**  
   * Initialise `fleetCount = 0` and `slowest = -1` (the arrival time of the last formed fleet).  
   * For each car in the sorted order:  
     - If `time > slowest` (or `slowest == -1`), this car cannot catch the fleet ahead → start a new fleet: `fleetCount++` and set `slowest = time`.  
     - Otherwise `time ≤ slowest`; the car merges into the current fleet and we do nothing.

4. Return `fleetCount`.

---

## Complexity Analysis

|                | Complexity | Reason                                      |
|----------------|------------|---------------------------------------------|
| **Time**       | $O(n \log n)$ | Sorting `n` pairs dominates the runtime.   |
| **Space**      | $O(n)$       | Storing the `(position, time)` pairs (or a stack). |

---

## Key Takeaways

- **Time‑based reduction**: Converting distance & speed to a single scalar (`arrival time`) turns a motion problem into a simple ordering problem.  
- **Monotonic scan**: After sorting by position, the fleet formation rule is monotone; a single pass suffices, eliminating the need for a full stack.  
- **Greedy correctness**: The farthest car’s fleet time is a hard lower bound for any car behind it; any car with a larger time must start a new fleet.  
- **Precision safety**: With `target ≤ 10^6` and `speed ≤ 10^6`, double precision provides enough accuracy for the comparisons, so no epsilon handling is required.

---

## My Original Solution

```cpp
class Solution {
public:
    static bool positionComparator(const pair<int, double> &a, const pair<int, double> &b){
        return a.first < b.first;
    }
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, double>> timeTaken;
        for(int i = 0;i < position.size();i++){
            timeTaken.push_back({position[i], (double)(target - position[i])/ speed[i]});
        }
        sort(timeTaken.begin(), timeTaken.end(), positionComparator);

        stack<double> destTime;
        for(int i = 0;i < timeTaken.size(); i++){
            while(!destTime.empty() && timeTaken[i].second >= destTime.top()) destTime.pop();
            destTime.push(timeTaken[i].second);
        }
        return destTime.size();
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int carFleet(int target, const vector<int>& position, const vector<int>& speed) {
        int n = position.size();
        // Pair each car's start position with its arrival time.
        vector<pair<int, double>> cars;
        cars.reserve(n);
        for (int i = 0; i < n; ++i) {
            double t = static_cast<double>(target - position[i]) / speed[i];
            cars.emplace_back(position[i], t);
        }

        // Sort from the car closest to the target to the farthest.
        sort(cars.begin(), cars.end(),
             [](const auto& a, const auto& b) { return a.first > b.first; });

        int fleets = 0;
        double slowest = -1.0;               // arrival time of the last formed fleet
        for (const auto& [pos, t] : cars) {
            if (t > slowest) {               // cannot catch the fleet ahead
                ++fleets;
                slowest = t;                 // this fleet becomes the new slowest
            }
            // else: joins current fleet, nothing to do
        }
        return fleets;
    }
};
```

## Code Walkthrough

- **Line 7‑11**: Build a vector `cars` where each element holds `(position, arrivalTime)`. The division is cast to `double` to keep fractional times.  
- **Line 14‑16**: Sort `cars` **descending** by `position`. Scanning in this order guarantees that when we look at a car, all cars ahead of it (closer to the target) have already been processed.  
- **Line 19‑25**: Maintain `slowest`, the largest arrival time among fleets formed so far.  
  - If the current car’s `t` is larger than `slowest`, it cannot catch any fleet ahead → start a new fleet (`fleets++`) and update `slowest`.  
  - Otherwise (`t ≤ slowest`) the car will eventually merge with the fleet whose arrival time is `slowest`; no counter update is needed.  
- **Line 27**: Return the total number of distinct fleets.
