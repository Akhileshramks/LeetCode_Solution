# 3934. Smallest Unique Subarray

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Hash Table, Binary Search, Rolling Hash, Suffix Array, Hash Function &nbsp;|&nbsp; **Solved:** May 22, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 750 ms &nbsp;|&nbsp; **Memory:** 363238.3 MB

---

## Problem

You are given an integer array `nums`.

Find the **minimum **length of a subarray that is **not** **identical** to any other **subarray** in `nums`.

Return an integer denoting the **minimum possible length** of such a **subarray**.

Two **subarrays** are considered identical if they have the same length and the same elements in corresponding positions.

 

**Example 1:**

**Input:** nums = [3,3,3]

**Output:** 3

**Explanation:**

	
- Subarrays of length 1: `[3]` &rarr; appears 3 times
	
- Subarrays of length 2: `[3, 3]` &rarr; appears 2 times
	
- Subarrays of length 3: `[3, 3, 3]` &rarr; appears once

The subarray `[3, 3, 3]` is unique, so the smallest unique subarray length is 3.

**Example 2:**

**Input:** nums = [2,1,2,3,3]

**Output:** 1

**Explanation:**

Subarrays of length 1:

	
- `[2]` &rarr; appears 2 times
	
- `[1]` &rarr; appears once
	
- `[3]` &rarr; appears 2 times

The subarray `[1]` is unique, so the smallest unique subarray length is 1.

**Example 3:**

**Input:** nums = [1,1,2,2,1]

**Output:** 2

**Explanation:**

Subarrays of length 1:

	
- `[1]` &rarr; appears 3 times
	
- `[2]` &rarr; appears 2 times

Subarrays of length 2:

	
- `[1, 1]` &rarr; appears once
	
- `[1, 2]` &rarr; appears once
	
- `[2, 2]` &rarr; appears once
	
- `[2, 1]` &rarr; appears once

There is at least one subarray of length 2 that is unique, so the smallest unique subarray length is 2.

## Constraints

- `1 <= nums.length <= 105`
	
- `1 <= nums[i] <= 105`

## Hints

1. Think in terms of checking a fixed length `len`: count all subarrays of length `len`, and see whether any one appears exactly once.
2. Use rolling hash so each subarray can be represented in `O(1)` after preprocessing, instead of comparing arrays directly.
3. The answer can be binary searched because if there is a unique subarray of length `len`, then there is also a unique subarray of some length `> len`.
4. For each checked length, store frequencies of hashes in a hashmap. If any hash has frequency 1, that length works.

---

## Intuition

The fundamental insight that makes this solution possible is the use of a rolling hash function to efficiently compare subarrays of different lengths. By utilizing a prime number $p$ and a modulo operation $MOD$, we can create a unique hash value for each subarray, allowing us to quickly identify duplicate subarrays. The choice of a rolling hash function is crucial, as it enables us to calculate the hash value of a subarray in $O(1)$ time, making the overall solution efficient for large inputs.

## Approach

1. Define a helper function `isPossible` that takes an array `nums` and a length `len` as input. This function checks if there exists a unique subarray of length `len` in `nums`.
2. Initialize a prime number $p$ and a modulo operation $MOD$ to create a rolling hash function.
3. Calculate the hash value of the first subarray of length `len` using the rolling hash function.
4. Iterate through the remaining subarrays of length `len` and calculate their hash values using the rolling hash function.
5. Store the hash values in an unordered map `mpp` to keep track of the frequency of each hash value.
6. Check if there exists a hash value in `mpp` with a frequency of 1, indicating a unique subarray of length `len`.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n \log n)$ | The `isPossible` function iterates through the array `nums` and calculates the hash values for each subarray, resulting in a time complexity of $O(n)$. The binary search in the `smallestUniqueSubarray` function has a time complexity of $O(\log n)$. Therefore, the overall time complexity is $O(n \log n)$. |
| **Space** | $O(n)$ | The unordered map `mpp` stores the hash values for each subarray, resulting in a space complexity of $O(n)$.

## Key Takeaways

* The use of a rolling hash function allows for efficient comparison of subarrays, reducing the time complexity of the solution.
* The choice of a prime number $p$ and a modulo operation $MOD$ is crucial in creating a unique hash value for each subarray.
* The binary search approach in the `smallestUniqueSubarray` function enables us to find the minimum length of a unique subarray in $O(\log n)$ time.
* The use of an unordered map `mpp` to store the frequency of each hash value allows for efficient identification of unique subarrays.

## My Original Solution

```cpp
class Solution {
public:
    bool isPossible(vector<int>& nums, int len){
        long long prime = 1e5 + 3;
        long long MOD = (1LL << 31) - 1;
        long long power = 1, hash = 0;
        int n = nums.size();
        unordered_map<long long,int> mpp;
        for(int i = 0;i < len;i++){
            power = (power * prime) % MOD;
            hash = ((prime * hash) + nums[i]) % MOD;
        }
        mpp[hash]++;
        for(int i = len; i < n;i++){
            hash = ((hash * prime) + nums[i] - nums[i - len] * power) % MOD;
            hash = (hash + MOD) % MOD;
            mpp[hash]++;
        }
        for(auto [key, val] : mpp) if(val == 1) return true;
        return false;
    }
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int low = 1, high = n;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(isPossible(nums, mid)) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    /**
     * Checks if there exists a unique subarray of length len in nums.
     *
     * @param nums The input array.
     * @param len The length of the subarray.
     * @return True if a unique subarray exists, false otherwise.
     */
    bool hasUniqueSubarray(const vector<int>& nums, int len) {
        const long long prime = 1e5 + 3;
        const long long MOD = (1LL << 31) - 1;
        long long power = 1;
        long long hash = 0;
        unordered_map<long long, int> hashCount;

        // Calculate the hash value of the first subarray
        for (int i = 0; i < len; i++) {
            power = (power * prime) % MOD;
            hash = ((prime * hash) + nums[i]) % MOD;
        }
        hashCount[hash]++;

        // Calculate the hash values of the remaining subarrays
        for (int i = len; i < nums.size(); i++) {
            hash = ((hash * prime) + nums[i] - nums[i - len] * power) % MOD;
            hash = (hash + MOD) % MOD;
            hashCount[hash]++;
        }

        // Check if there exists a hash value with a frequency of 1
        for (const auto& pair : hashCount) {
            if (pair.second == 1) {
                return true;
            }
        }
        return false;
    }

    /**
     * Finds the minimum length of a unique subarray in nums.
     *
     * @param nums The input array.
     * @return The minimum length of a unique subarray.
     */
    int smallestUniqueSubarray(vector<int>& nums) {
        int low = 1;
        int high = nums.size();

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueSubarray(nums, mid)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
```

## Code Walkthrough

The key transformation in the code is the use of a rolling hash function to efficiently calculate the hash values of subarrays. The `hasUniqueSubarray` function calculates the hash value of the first subarray and then iterates through the remaining subarrays, updating the hash value using the rolling hash function. The `smallestUniqueSubarray` function uses a binary search approach to find the minimum length of a unique subarray.
