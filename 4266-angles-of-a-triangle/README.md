# 4266. Angles of a Triangle

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** N/A &nbsp;|&nbsp; **Solved:** April 18, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 28293.0 MB

---

## Problem Summary

You are given a positive integer array `sides` of length 3.

Determine if there exists a triangle with **positive** area whose three side lengths are given by the elements of `sides`.

If such a triangle exists, return an array of three floating-point numbers representing its internal angles (in **degrees**), **sorted** in **non-decreasing** order. Otherwise, return an empty array.

Answers within `10-5` of the actual answer will be accepted.

 

**Example 1:**

**Input:** sides = [3,4,5]

**Output:** [36.86990,53.13010,90.00000]

**Explanation:**

You can form a right-angled triangle with side lengths 3, 4, and 5. The internal angles of this triangle are approximately 36.869897646, 53.130102354, and 90 degrees respectively.

**Example 2:**

**Input:** sides = [2,4,2]

**Output:** []

**Explanation:**

You cannot form a triangle with positive area using side lengths 2, 4, and 2.

 

**Constraints:**

	
• `sides.length == 3`
	
• `1 <= sides[i] <= 1000`

## Hints

1. Sort the sides first, then check the triangle inequality: after sorting, it is enough to verify `a + b > c`.
2. If valid, use the law of cosines to compute each angle in radians, then convert to degrees.
3. Sort the three angles before returning; if the triangle is invalid, return an empty array.

## Intuition

> _Fill this in — what was the key insight that led to your solution?_

## Approach

> _Describe your algorithm step by step._

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(1) | _explain_ |
| **Space** | O(1) | _explain_ |

## Solution

```cpp
class Solution {
public:
    vector<double> internalAngles(vector<int>& sides) {
        sort(sides.begin(),sides.end());
        if(sides[0] + sides[1] <= sides[2]) return {};
        // a^2 = b^2 + c^2 - 2bc cosA
        // A = cos^-1(a^2 - b^2 - c^2 / 2bc)
        int a = sides[0], b = sides[1], c = sides[2];
        double A = ((acos((b*b + c*c - a*a)/(2.0*b*c)))/M_PI)*180;
        double B = ((acos((a*a + c*c - b*b)/(2.0*a*c)))/M_PI)*180;
        double C = ((acos((b*b + a*a - c*c)/(2.0*b*a)))/M_PI)*180;
        vector<double> res = {A,B,C};
        sort(res.begin(), res.end());
        return res;
    }
};
```

## Key Takeaways

- _Pattern used:_
- _Edge cases:_
- _Common mistakes:_
- _Related problems:_
