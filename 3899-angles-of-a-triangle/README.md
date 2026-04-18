# 3899. Angles of a Triangle

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** N/A &nbsp;|&nbsp; **Solved:** April 18, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 28293.0 MB

---

## Problem Summary

Given a positive integer array `sides` of length 3, determine if there exists a triangle with positive area whose three side lengths are given by the elements of `sides`. If such a triangle exists, return an array of three floating-point numbers representing its internal angles in degrees, sorted in non-decreasing order. Otherwise, return an empty array.

## Examples

* **Input:** sides = [3,4,5]
* **Output:** [36.86990,53.13010,90.00000]
* **Explanation:** A right-angled triangle can be formed with side lengths 3, 4, and 5, resulting in internal angles of approximately 36.869897646, 53.130102354, and 90 degrees respectively.
* **Input:** sides = [2,4,2]
* **Output:** []
* **Explanation:** No triangle with positive area can be formed using side lengths 2, 4, and 2.

## Intuition

The approach works by first checking if the given sides can form a valid triangle. This is done by sorting the sides and verifying that the sum of the two smallest sides is greater than the largest side (triangle inequality). If the sides are valid, we use the law of cosines to calculate each internal angle. The law of cosines states that for any triangle with sides a, b, and c, and angle A opposite side a, the following equation holds: a^2 = b^2 + c^2 - 2bc * cos(A). By rearranging this equation, we can solve for cos(A) and then use the inverse cosine function (acos) to find angle A. This process is repeated for the other two angles, and the results are sorted before being returned.

## Approach

1. Sort the sides of the triangle in non-decreasing order.
2. Check if the sum of the two smallest sides is greater than the largest side (triangle inequality). If not, return an empty array.
3. Use the law of cosines to calculate each internal angle of the triangle.
4. Convert the angles from radians to degrees.
5. Sort the angles in non-decreasing order and return the result.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(1) | The algorithm performs a constant number of operations, including sorting the sides, checking the triangle inequality, and calculating the internal angles. |
| **Space** | O(1) | The algorithm uses a constant amount of space to store the sides and angles. |

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

## Code Walkthrough

The code first sorts the sides of the triangle using the `sort` function. It then checks if the sum of the two smallest sides is greater than the largest side by comparing `sides[0] + sides[1]` with `sides[2]`. If the sides do not form a valid triangle, an empty array is returned. Otherwise, the code calculates each internal angle using the law of cosines and the `acos` function. The angles are converted from radians to degrees by multiplying by `180 / M_PI`. Finally, the angles are sorted in non-decreasing order using the `sort` function and returned as a vector.

## Key Takeaways

- **Pattern:** Triangle inequality and law of cosines for calculating internal angles.
- **Edge cases:** Invalid triangles (e.g., sides that do not satisfy the triangle inequality).
- **Common mistake:** Forgetting to check the triangle inequality before calculating the internal angles.
- **Related problems:** Other problems involving triangle geometry, such as calculating the area or perimeter of a triangle given its sides.