# 3464. Maximize the Distance Between Points on a Square

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Math, Binary Search, Geometry, Sorting &nbsp;|&nbsp; **Solved:** April 25, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 83 ms &nbsp;|&nbsp; **Memory:** 47160.2 MB

---

## Problem

You are given an integer `side`, representing the edge length of a square with corners at `(0, 0)`, `(0, side)`, `(side, 0)`, and `(side, side)` on a Cartesian plane.

You are also given a **positive** integer `k` and a 2D integer array `points`, where `points[i] = [xi, yi]` represents the coordinate of a point lying on the **boundary** of the square.

You need to select `k` elements among `points` such that the **minimum** Manhattan distance between any two points is **maximized**.

Return the **maximum** possible **minimum** Manhattan distance between the selected `k` points.

The Manhattan Distance between two cells `(xi, yi)` and `(xj, yj)` is `|xi - xj| + |yi - yj|`.

 

**Example 1:**

**Input:** side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

**Output:** 2

**Explanation:**

![](https://assets.leetcode.com/uploads/2025/01/28/4080_example0_revised.png)

Select all four points.

**Example 2:**

**Input:** side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

**Output:** 1

**Explanation:**

![](https://assets.leetcode.com/uploads/2025/01/28/4080_example1_revised.png)

Select the points `(0, 0)`, `(2, 0)`, `(2, 2)`, and `(2, 1)`.

**Example 3:**

**Input:** side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

**Output:** 1

**Explanation:**

![](https://assets.leetcode.com/uploads/2025/01/28/4080_example2_revised.png)

Select the points `(0, 0)`, `(0, 1)`, `(0, 2)`, `(1, 2)`, and `(2, 2)`.

## Constraints

- `1 <= side <= 109`
	
- `4 <= points.length <= min(4 * side, 15 * 103)`
	
- `points[i] == [xi, yi]`
	
- The input is generated such that:
	

		
- `points[i]` lies on the boundary of the square.
		
- All `points[i]` are **unique**.
	

	
	
- `4 <= k <= min(25, points.length)`

## Hints

1. Can we use binary search for this problem?
2. Think of the coordinates on a straight line in clockwise order.
3. Binary search on the minimum Manhattan distance `x`.
4. During the binary search, for each coordinate, find the immediate next coordinate with distance >= `x`.
5. Greedily select up to `k` coordinates.

---

## Intuition

The boundary of a square is a **closed loop** of length $4\cdot\text{side}$.  
If every point on the boundary is projected onto this loop as a single scalar distance measured clockwise from a fixed origin (e.g., $(0,0)$), the Manhattan distance between two boundary points becomes the **circular distance** along the loop:

\[
d_{\text{man}}(p_i,p_j)=\min\big(|c_i-c_j|,\;4\cdot\text{side}-|c_i-c_j|\big)
\]

Thus the original 2‑D problem reduces to: *choose $k$ numbers on a circle of circumference $C=4\cdot\text{side}$ so that the minimal circular gap is maximized*.  
For a fixed candidate distance $D$, the feasibility test is a classic greedy “pick the next point at least $D$ ahead” problem, with the extra wrap‑around condition that the distance from the last selected point back to the first must also be $\ge D$.  
Because feasibility is monotone in $D$, we can binary‑search the answer.

---

## Approach

1. **Linearize the perimeter**  
   * For each point `(x,y)` on the boundary compute its clockwise distance `c` from `(0,0)`:
     * bottom edge (`y==0`): `c = x`
     * right edge (`x==side`): `c = side + y`
     * top edge (`y==side`): `c = 3·side - x`
     * left edge (`x==0`): `c = 4·side - y`
   * Store all `c` in a vector `pos` and sort it.

2. **Binary search on the answer**  
   * Low = 0, High = $4·\text{side}$.  
   * While `low ≤ high`:
     * `mid = (low+high)/2`.
     * If `canPlace(mid)` is true → `low = mid + 1`; else `high = mid - 1`.

3. **Greedy feasibility check `canPlace(D)`**  
   * Try every possible start index `s` (0 … $n-1$).  
   * Set `prev = s`, `cnt = 1`.  
   * Repeatedly find the first point `next` with `pos[next] ≥ pos[prev] + D` using `lower_bound`.  
   * If `next` exists and the **circular gap** from `next` back to `s` (`C - pos[next] + pos[s]`) is also ≥ $D$, accept `next` and continue.  
   * Stop when `cnt == k` (feasible) or when no further point satisfies the condition.  
   * If any start succeeds, `canPlace(D)` returns true.

4. Return `high`, the largest feasible distance.

---

## Complexity Analysis

|                | Complexity | Reason |
|----------------|------------|--------|
| **Time**       | $O\!\left(n\log n + \log(4\cdot\text{side})\cdot n\log n\right)$ | Sorting `pos` costs $O(n\log n)$. Each binary‑search step runs `canPlace`, which iterates at most $n$ starts and uses a `lower_bound` ($O(\log n)$) per selection. |
| **Space**      | $O(n)$ | The linearized coordinate array `pos`. |

(With $n = |\text{points}|$.)

---

## Key Takeaways

* **Perimeter linearization** turns a 2‑D Manhattan distance problem on a square’s boundary into a 1‑D circular spacing problem.  
* **Circular feasibility** requires checking both the forward gap (`≥ D`) and the wrap‑around gap (`C - last + first ≥ D`).  
* **Monotonicity** of the feasibility predicate enables a binary search on the answer, yielding a logarithmic factor over the search space $[0,4·\text{side}]$.  
* Using `lower_bound` (binary search) inside the greedy check keeps each feasibility test at $O(n\log n)$ instead of $O(n^2)$, which is crucial for the given constraints.

---

## My Original Solution

```cpp
class Solution {
public:
    bool isPossible(vector<long long>& nums, long long target, int k, int n,int side){
        for(int start = 0;start < n - k + 1;start++){
            int prev  = start;
            int want = k - 1;
            while(want > 0 && prev < n){
                int curr = lower_bound(nums.begin() + prev + 1, nums.end(), nums[prev] + target) - nums.begin();
                if(curr == n) break;
                if((1ll * 4 * side - nums[curr] + nums[start]) >= target){
                    prev = curr;
                    want--;
                }else{
                    break;
                }
            }
            if(want == 0) return true;
        }
        return false;
    }
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> nums;
        for(auto i : points){
            if(i[1] == 0) nums.push_back(i[0]);
            else if(i[0] == side) nums.push_back(side + i[1]);
            else if(i[1] == side) nums.push_back(1ll * 3 * side - i[0]);
            else if(i[0] == 0) nums.push_back(1ll * 4 * side - i[1]);
        }
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long low = 0, high = 1ll * 4 * side;
        while(low <= high){
            long long mid = low + (high - low) / 2;
            if(isPossible(nums, mid, k, n, side)) low = mid + 1;
            else high = mid - 1; 
        }
        return high;
    }
};
```

## Professional Refactor

```cpp
// language: cpp
class Solution {
public:
    // Check if we can select k points with minimum circular distance >= dist
    bool canPlace(const vector<long long>& pos, long long dist, int k, long long perim) {
        int n = pos.size();
        for (int start = 0; start < n; ++start) {
            int last = start;          // index of the most recently chosen point
            int placed = 1;            // we have placed the start point
            while (placed < k) {
                // find the first point at least dist ahead of pos[last]
                long long need = pos[last] + dist;
                int nxt = lower_bound(pos.begin() + last + 1, pos.end(), need) - pos.begin();
                if (nxt == n) break;   // no further point in linear order
                // ensure the circular gap from nxt back to start also satisfies dist
                if (perim - pos[nxt] + pos[start] < dist) break;
                last = nxt;
                ++placed;
            }
            if (placed == k) return true;
        }
        return false;
    }

    // Convert a boundary point to its clockwise distance from (0,0)
    long long toLinear(int x, int y, int side) const {
        if (y == 0)               return x;                           // bottom
        if (x == side)            return side + y;                    // right
        if (y == side)            return 3LL * side - x;               // top
        /* x == 0 */              return 4LL * side - y;               // left
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) override {
        const long long perim = 4LL * side;
        vector<long long> pos;
        pos.reserve(points.size());
        for (const auto& p : points)
            pos.push_back(toLinear(p[0], p[1], side));

        sort(pos.begin(), pos.end());

        long long lo = 0, hi = perim;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (canPlace(pos, mid, k, perim))
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return static_cast<int>(hi);
    }
};
```

## Code Walkthrough

* **`toLinear`** – maps a boundary coordinate to a single scalar on the clockwise loop. The four `if` branches correspond to the four edges; the formulas follow the perimeter order bottom → right → top → left.
* **`canPlace`** – implements the greedy feasibility test:
  * For each possible start index we try to greedily pick the next point at least `dist` ahead using `lower_bound`.
  * The additional condition `perim - pos[nxt] + pos[start] >= dist` guarantees the **wrap‑around gap** (last → first) also respects the candidate distance.
  * If we succeed in placing `k` points, the distance `dist` is feasible.
* **Binary search** – standard monotone search on `[0, perim]`. `hi` ends up as the largest feasible distance, which is the required answer.
