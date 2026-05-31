# 2126. Destroying Asteroids

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Greedy, Sorting &nbsp;|&nbsp; **Solved:** May 31, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 37 ms &nbsp;|&nbsp; **Memory:** 104335.9 MB

---

## Problem

You are given an integer `mass`, which represents the original mass of a planet. You are further given an integer array `asteroids`, where `asteroids[i]` is the mass of the `ith` asteroid.

You can arrange for the planet to collide with the asteroids in **any arbitrary order**. If the mass of the planet is **greater than or equal to** the mass of the asteroid, the asteroid is **destroyed** and the planet **gains** the mass of the asteroid. Otherwise, the planet is destroyed.

Return `true`_ if **all** asteroids can be destroyed. Otherwise, return _`false`_._

 

**Example 1:**

> **Input:** mass = 10, asteroids = [3,9,19,5,21]
> **Output:** true
> **Explanation:** One way to order the asteroids is [9,19,5,3,21]:
> - The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
> - The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
> - The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
> - The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
> - The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
> All asteroids are destroyed.

**Example 2:**

> **Input:** mass = 5, asteroids = [4,9,23,4]
> **Output:** false
> **Explanation:** 
> The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
> After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
> This is less than 23, so a collision would not destroy the last asteroid.

## Constraints

- `1 <= mass <= 105`
	
- `1 <= asteroids.length <= 105`
	
- `1 <= asteroids[i] <= 105`

## Hints

1. Choosing the asteroid to collide with can be done greedily.
2. If an asteroid will destroy the planet, then every bigger asteroid will also destroy the planet.
3. You only need to check the smallest asteroid at each collision. If it will destroy the planet, then every other asteroid will also destroy the planet.
4. Sort the asteroids in non-decreasing order by mass, then greedily try to collide with the asteroids in that order.

---

## Intuition

The "Aha!" moment in this problem is the realization that the asteroids should be destroyed in a specific order to maximize the planet's mass at each step. This can be achieved by sorting the asteroids in ascending order of their masses. By doing so, the planet can destroy the smaller asteroids first and gain their mass, increasing its chances of destroying the larger asteroids later on. This greedy approach works because the planet's mass is always increasing, allowing it to tackle larger asteroids as it progresses.

## Approach

1. Sort the asteroids in ascending order of their masses to ensure that the planet destroys the smallest asteroids first.
2. Initialize a variable `sum` to the initial mass of the planet and iterate through the sorted asteroids.
3. For each asteroid, check if the planet's current mass is greater than or equal to the asteroid's mass. If it is, update the planet's mass by adding the asteroid's mass to it.
4. If the planet's mass is not sufficient to destroy the current asteroid, return `false` as it is not possible to destroy all asteroids.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n \log n)$ | The sorting operation takes $O(n \log n)$ time, where $n$ is the number of asteroids. The subsequent for loop takes $O(n)$ time, but it is dominated by the sorting operation. |
| **Space** | $O(1)$ | The space complexity is $O(1)$ as we only use a constant amount of space to store the planet's mass and the asteroid's mass. |

## Key Takeaways

* Sorting the asteroids in ascending order of their masses is crucial to maximize the planet's mass at each step.
* The greedy approach works because the planet's mass is always increasing, allowing it to tackle larger asteroids later on.
* The use of a `long long` data type is necessary to avoid integer overflow when updating the planet's mass.
* The `min` function is used to prevent overflow when adding the asteroid's mass to the planet's mass.

## My Original Solution

```cpp
class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());
        int n = asteroids.size();\
        long long sum = mass;
        for(int i = 0;i < n;i++){
            if(asteroids[i] <= sum) sum = min(1LL * asteroids[i] + sum, (long long)INT_MAX);
            else return false;
        }
        return true;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    bool asteroidsDestroyed(int initialMass, vector<int>& asteroids) {
        // Sort asteroids in ascending order of their masses
        sort(asteroids.begin(), asteroids.end());
        
        long long currentMass = initialMass;
        for (const int asteroidMass : asteroids) {
            // Check if the planet's current mass is sufficient to destroy the asteroid
            if (asteroidMass <= currentMass) {
                // Update the planet's mass by adding the asteroid's mass
                currentMass = min(asteroidMass + currentMass, (long long)INT_MAX);
            } else {
                // If the planet's mass is not sufficient, return false
                return false;
            }
        }
        // If all asteroids are destroyed, return true
        return true;
    }
};
```

## Code Walkthrough

The key transformation in this algorithm is the sorting of the asteroids in ascending order of their masses. This allows the planet to destroy the smaller asteroids first and gain their mass, increasing its chances of destroying the larger asteroids later on. The use of a `long long` data type and the `min` function prevents integer overflow when updating the planet's mass.
