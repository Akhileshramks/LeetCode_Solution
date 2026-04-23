# 2615. Sum of Distances

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Hash Table, Prefix Sum &nbsp;|&nbsp; **Solved:** April 23, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 71 ms &nbsp;|&nbsp; **Memory:** 105.7 MB

---

## Problem

You are given a **0-indexed** integer array `nums`. There exists an array `arr` of length `nums.length`, where `arr[i]` is the sum of `|i - j|` over all `j` such that `nums[j] == nums[i]` and `j != i`. If there is no such `j`, set `arr[i]` to be `0`.

Return _the array _`arr`_._

 

**Example 1:**

> **Input:** nums = [1,3,1,1,2]
> **Output:** [5,0,3,4,0]
> **Explanation:** 
> When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
> When i = 1, arr[1] = 0 because there is no other index with value 3.
> When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
> When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
> When i = 4, arr[4] = 0 because there is no other index with value 2.

**Example 2:**

> **Input:** nums = [0,5,3]
> **Output:** [0,0,0]
> **Explanation:** Since each element in nums is distinct, arr[i] = 0 for all i.

## Constraints

- `1 <= nums.length <= 105`
	
- `0 <= nums[i] <= 109`

 

**Note:** This question is the same as  2121: Intervals Between Identical Elements.

## Hints

1. Can we use the prefix sum here?
2. For each number x, collect all the indices where x occurs, and calculate the prefix sum of the array.
3. For each occurrence of x, the indices to the right will be regular subtraction while the indices to the left will be reversed subtraction.

---

## Intuition  

The distance sum for an index `i` only involves other positions that hold the **same value**.  
If we sort those positions (they are naturally ordered by their indices), the absolute‑difference sum can be expressed with prefix information:

\[
\sum_{j < i,\,\text{same}} |i-j|
   = i\cdot\text{cnt}_{\text{left}} - \text{sumIdx}_{\text{left}}
\]

\[
\sum_{j > i,\,\text{same}} |i-j|
   = \text{sumIdx}_{\text{right}} - i\cdot\text{cnt}_{\text{right}}
\]

Thus, for each value we only need two aggregates while scanning the array:

* `cnt` – how many times the value has been seen so far.  
* `sumIdx` – the sum of those indices.

A **single pass** gives the left‑side contribution; a **second pass** (from the opposite direction) yields the right‑side contribution. This reduces the problem to $O(n)$ time with $O(\text{distinct})$ extra space.

---

## Approach  

1. **First pass (left‑to‑right)**  
   * Maintain `cnt` and `sumIdx` for each value in a hash map.  
   * For the current index `i`, compute the contribution from all previous equal elements:  
     `left = i * cnt[value] - sumIdx[value]`.  
   * Add `left` to `answer[i]`.  
   * Update the map: `cnt[value]++`, `sumIdx[value] += i`.

2. **Second pass (right‑to‑left)**  
   * Clear the map (or use a fresh one).  
   * Iterate from `n‑1` down to `0`.  
   * For index `i`, compute the contribution from all **later** equal elements:  
     `right = sumIdx[value] - i * cnt[value]`.  
   * Add `right` to `answer[i]`.  
   * Update the map as in step 1.

3. Return the filled `answer` array.

---

## Complexity Analysis  

|               | Complexity | Reason                                                                 |
|---------------|------------|------------------------------------------------------------------------|
| **Time**      | $O(n)$     | Two linear scans; each map operation is $O(1)$ amortized.             |
| **Space**     | $O(u)$     | Hash map stores `cnt` + `sumIdx` for each distinct value $u \le n$.   |

---

## Key Takeaways  

* **Prefix‑sum trick for absolute differences** – converting $\sum|i-j|$ into a linear expression using count and index‑sum eliminates the need for nested loops.  
* **Two‑direction sweep** – a left‑to‑right pass handles “previous” contributions, while a right‑to‑left pass handles “next” contributions; together they give the full answer in linear time.  
* **Per‑value aggregation** – storing only two scalars per distinct number is sufficient; no need to keep the full list of indices.  
* **Long‑long safety** – with $n\le10^5$ and indices up to $10^5$, the total distance can reach $\approx 10^{10}$, so 64‑bit integers are required.

---

## My Original Solution

```cpp
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        int MOD = 1e9 + 7;
        long long leftSum = 0, rightSum = 0;
        vector<long long> res(n,0);
        unordered_map<int,pair<long long,long long>> mpp;
        for(int i = n-1;i >= 0;i--){
            if(mpp.find(nums[i]) != mpp.end()){
                leftSum = mpp[nums[i]].first;
                rightSum = i * mpp[nums[i]].second; 
                res[i] += leftSum - rightSum;
            }
            mpp[nums[i]].first += i;
            mpp[nums[i]].second++;
        }
        mpp.clear();
        for(int i = 0;i < n;i++){
            if(mpp.find(nums[i]) != mpp.end()){
                leftSum = mpp[nums[i]].first;
                rightSum = i * mpp[nums[i]].second; 
                res[i] += rightSum - leftSum;
            }
            mpp[nums[i]].first += i;
            mpp[nums[i]].second++;
        }
        return res;
    }
};

/*

0 1 2 3 4 5 6
1 - 1 - 1 1 -


5 - 4 = 1

5 - 2 = 3 
4 - 2 = 2 

5 - 1 => 4
4 - 1 => 3 
2 - 1 => 1

*/

```

## Professional Refactor

```cpp
// 2615. Sum of Distances
// O(n) time, O(distinct) space
class Solution {
public:
    vector<long long> sumOfDistances(const vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        vector<long long> ans(n, 0);

        // ---------- left side contribution ----------
        unordered_map<int, pair<long long, long long>> pref; // {value -> {sumIdx, cnt}}
        for (int i = 0; i < n; ++i) {
            auto& entry = pref[nums[i]];
            long long sumIdx = entry.first;   // Σ previous indices with this value
            long long cnt    = entry.second;  // how many previous indices

            // distance to all previous equal elements
            ans[i] += static_cast<long long>(i) * cnt - sumIdx;

            // update aggregates for future positions
            entry.first += i;
            ++entry.second;
        }

        // ---------- right side contribution ----------
        pref.clear(); // reuse the map for the reverse pass
        for (int i = n - 1; i >= 0; --i) {
            auto& entry = pref[nums[i]];
            long long sumIdx = entry.first;   // Σ later indices with this value
            long long cnt    = entry.second;  // how many later indices

            // distance to all later equal elements
            ans[i] += sumIdx - static_cast<long long>(i) * cnt;

            // update aggregates for earlier positions
            entry.first += i;
            ++entry.second;
        }

        return ans;
    }
};
```

## Code Walkthrough  

* **`pref` map** – each key holds a pair `{sumIdx, cnt}`.  
  * `sumIdx` accumulates the **indices** of already‑seen (or later‑seen) occurrences.  
  * `cnt` counts how many such occurrences exist.  

* **First loop (`i = 0 … n‑1`)**  
  * `ans[i] += i * cnt - sumIdx` computes the left contribution using the formula derived in the intuition.  
  * After processing `i`, we add `i` to `sumIdx` and increment `cnt` so that future positions treat `i` as a “previous” element.  

* **Second loop (`i = n‑1 … 0`)**  
  * The same map is reused (cleared first).  
  * Now `sumIdx` and `cnt` represent **later** occurrences because we are scanning backwards.  
  * `ans[i] += sumIdx - i * cnt` adds the right contribution.  

* **Why `long long`?**  
  * The maximum possible sum is on the order of $n^2$ (≈ $10^{10}$), which exceeds 32‑bit range.  

The two passes together fill `ans` with the exact sum of distances for every index in linear time.
