# 1665. Minimum Initial Energy to Finish Tasks

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Greedy, Sorting &nbsp;|&nbsp; **Solved:** May 12, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 2007 ms &nbsp;|&nbsp; **Memory:** 494914.1 MB

---

## Problem

You are given an array `tasks` where `tasks[i] = [actuali, minimumi]`:

	
- `actuali` is the actual amount of energy you **spend to finish** the `ith` task.
	
- `minimumi` is the minimum amount of energy you **require to begin** the `ith` task.

For example, if the task is `[10, 12]` and your current energy is `11`, you cannot start this task. However, if your current energy is `13`, you can complete this task, and your energy will be `3` after finishing it.

You can finish the tasks in **any order** you like.

Return _the **minimum** initial amount of energy you will need_ _to finish all the tasks_.

 

**Example 1:**

> **Input:** tasks = [[1,2],[2,4],[4,8]]
> **Output:** 8
> **Explanation:**
> Starting with 8 energy, we finish the tasks in the following order:
>     - 3rd task. Now energy = 8 - 4 = 4.
>     - 2nd task. Now energy = 4 - 2 = 2.
>     - 1st task. Now energy = 2 - 1 = 1.
> Notice that even though we have leftover energy, starting with 7 energy does not work because we cannot do the 3rd task.

**Example 2:**

> **Input:** tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
> **Output:** 32
> **Explanation:**
> Starting with 32 energy, we finish the tasks in the following order:
>     - 1st task. Now energy = 32 - 1 = 31.
>     - 2nd task. Now energy = 31 - 2 = 29.
>     - 3rd task. Now energy = 29 - 10 = 19.
>     - 4th task. Now energy = 19 - 10 = 9.
>     - 5th task. Now energy = 9 - 8 = 1.

**Example 3:**

> **Input:** tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
> **Output:** 27
> **Explanation:**
> Starting with 27 energy, we finish the tasks in the following order:
>     - 5th task. Now energy = 27 - 5 = 22.
>     - 2nd task. Now energy = 22 - 2 = 20.
>     - 3rd task. Now energy = 20 - 3 = 17.
>     - 1st task. Now energy = 17 - 1 = 16.
>     - 4th task. Now energy = 16 - 4 = 12.
>     - 6th task. Now energy = 12 - 6 = 6.

## Constraints

- `1 <= tasks.length <= 105`
	
- `1 <= actual​i <= minimumi <= 104`

## Hints

1. We can easily figure that the f(x) : does x solve this array is monotonic so binary Search is doable
2. Figure a sorting pattern

---

## Intuition

The "Aha!" moment in this problem is realizing that the tasks should be sorted based on the difference between the minimum energy required to start a task and the actual energy spent to finish it. This is because we want to finish the tasks that require the most energy to start first, so that we can minimize the initial energy required. Additionally, if two tasks have the same difference, we should sort them based on the minimum energy required to start the task, so that we can finish the task that requires the most energy to start first.

## Approach

1. Sort the tasks based on the difference between the minimum energy required to start a task and the actual energy spent to finish it. If two tasks have the same difference, sort them based on the minimum energy required to start the task.
2. Initialize two variables, `res` and `scoreAdded`, to keep track of the current energy and the initial energy required, respectively.
3. Iterate through the sorted tasks. For each task, if the minimum energy required to start the task is less than or equal to the current energy, subtract the actual energy spent to finish the task from the current energy. Otherwise, add the difference between the minimum energy required to start the task and the current energy to the initial energy required, and update the current energy.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n log n)$ | The tasks are sorted using a custom comparator, which takes $O(n log n)$ time. The subsequent iteration through the tasks takes $O(n)$ time. |
| **Space** | $O(1)$ | The space complexity is constant, as only a few extra variables are used to store the current energy and the initial energy required. |

## Key Takeaways

* Sorting the tasks based on the difference between the minimum energy required to start a task and the actual energy spent to finish it allows us to minimize the initial energy required.
* Using a custom comparator to sort the tasks based on the difference and the minimum energy required to start the task ensures that tasks with the same difference are sorted correctly.
* The iteration through the sorted tasks can be done in a single pass, making the algorithm efficient.
* The use of two variables, `res` and `scoreAdded`, allows us to keep track of the current energy and the initial energy required, making the algorithm simple and easy to understand.

## My Original Solution

```cpp
class Solution {
public:
    static bool comparator(vector<int> a, vector<int> b){
        int diff1 = a[1] - a[0];
        int diff2 = b[1] - b[0];
        if(diff1 == diff2) return b[1] < a[1];
        if(diff1 > diff2) return true;
        return false;
    }
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), comparator);
        int res = 0;
        int scoreAdded = 0;
        for(auto i : tasks){
            if(i[1] <= res) res -= i[0];
            else{
                scoreAdded += i[1] - res;
                res += i[1] - res - i[0];
            }
        }
        return scoreAdded;
    }
};
/*
score = 12, res = 2
score = 14, res = 2
score = 15, res 
*/


```

## Professional Refactor

```cpp
class Solution {
public:
    // Custom comparator to sort tasks based on the difference between the minimum energy required to start a task and the actual energy spent to finish it
    static bool compareTasks(const vector<int>& a, const vector<int>& b) {
        int diffA = a[1] - a[0];
        int diffB = b[1] - b[0];
        if (diffA == diffB) {
            return b[1] < a[1];
        }
        return diffA > diffB;
    }

    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort tasks using the custom comparator
        sort(tasks.begin(), tasks.end(), compareTasks);
        
        int currentEnergy = 0;
        int initialEnergyRequired = 0;
        
        // Iterate through the sorted tasks
        for (const auto& task : tasks) {
            if (task[1] <= currentEnergy) {
                // If the minimum energy required to start the task is less than or equal to the current energy, subtract the actual energy spent to finish the task from the current energy
                currentEnergy -= task[0];
            } else {
                // Otherwise, add the difference between the minimum energy required to start the task and the current energy to the initial energy required, and update the current energy
                initialEnergyRequired += task[1] - currentEnergy;
                currentEnergy += task[1] - currentEnergy - task[0];
            }
        }
        
        return initialEnergyRequired;
    }
};
```

## Code Walkthrough

The code sorts the tasks based on the difference between the minimum energy required to start a task and the actual energy spent to finish it. It then iterates through the sorted tasks, updating the current energy and the initial energy required based on the minimum energy required to start each task and the actual energy spent to finish each task. The key transformation is the use of a custom comparator to sort the tasks, which allows us to minimize the initial energy required.
