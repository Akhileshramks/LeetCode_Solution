# 3913. Sort Vowels by Frequency

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** N/A &nbsp;|&nbsp; **Solved:** April 26, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 31 ms &nbsp;|&nbsp; **Memory:** 18003.9 MB

---

## Problem

You are given a string `s` consisting of lowercase English characters.

Rearrange only the **vowels** in the string so that they appear in **non-increasing** order of their frequency.

If multiple vowels have the same **frequency**, order them by the position of their **first occurrence** in `s`.

Return the modified string.

Vowels are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`.

The **frequency** of a letter is the number of times it occurs in the string.

 

**Example 1:**

**Input:** s = "leetcode"

**Output:** "leetcedo"

**Explanation:**​​​​​​​

	
- Vowels in the string are `['e', 'e', 'o', 'e']` with frequencies: `e = 3`, `o = 1`.
	
- Sorting in non-increasing order of frequency and placing them back into the vowel positions results in `"leetcedo"`.

**Example 2:**

**Input:** s = "aeiaaioooa"

**Output:** "aaaaoooiie"

**Explanation:**​​​​​​​

	
- Vowels in the string are `['a', 'e', 'i', 'a', 'a', 'i', 'o', 'o', 'o', 'a']` with frequencies: `a = 4`, `o = 3`, `i = 2`, `e = 1`.
	
- Sorting them in non-increasing order of frequency and placing them back into the vowel positions results in `"aaaaoooiie"`.

**Example 3:**

**Input:** s = "baeiou"

**Output:** "baeiou"

**Explanation:**

	
- Each vowel appears exactly once, so all have the same frequency.
	
- Thus, they retain their relative order based on first occurrence, and the string remains unchanged.

## Constraints

- `1 <= s.length <= 105`
	
- `s` consists of lowercase English letters

## Hints

1. Simulate as described

---

## Intuition

The only mutable characters are the **vowels**. Since there are only five possible vowels, we can treat their frequencies as a tiny histogram.  
If we know each vowel’s total count and the index of its **first** appearance, we can sort the *distinct* vowels by  

1. descending frequency,  
2. ascending first‑occurrence index (tie‑breaker).

Because the sorted order is fixed, we can greedily fill the vowel positions in the original string from left to right with the most‑frequent vowel until its quota is exhausted, then move to the next vowel. This “fill‑the‑slots” view eliminates any need for complex data structures.

---

## Approach

1. **Scan once** through `s`  
   * For every vowel `c` record `freq[c]++`.  
   * If `firstPos[c]` is still `-1`, set it to the current index `i`.  

2. **Collect distinct vowels** that actually appear (at most 5) into a vector `order`.

3. **Sort `order`** with a comparator:  
   * if `freq[a] != freq[b]` → larger frequency first;  
   * otherwise → smaller `firstPos` first.

4. **Re‑construct** the answer:  
   * Iterate `s` again.  
   * When a vowel is encountered, replace it by `order[cur]`.  
   * Decrease `freq[order[cur]]`; when it reaches 0, advance `cur` to the next vowel in `order`.

5. Return the modified string.

---

## Complexity Analysis

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(n + v\log v)$ | One linear scan (`n = |s|`) plus sorting at most $v = 5$ distinct vowels. |
| **Space**      | $O(v)$     | Frequency array, first‑position array and the `order` vector (constant ≤ 5). |

Since $v$ is bounded by 5, the overall time simplifies to $O(n)$ and space to $O(1)$.

---

## Key Takeaways

- **Histogram + first‑occurrence**: For a tiny alphabet (vowels) a simple array + first index captures both sorting keys without extra structures.  
- **Sort only distinct keys**: Limiting sorting to at most five elements turns an $O(k\log k)$ step into a constant‑time operation.  
- **Greedy slot‑filling** works because the sorted order is global; once the highest‑frequency vowel’s quota is placed, the remaining slots must be filled by the next vowel.  
- **In‑place reconstruction**: By reusing the original string as a mutable buffer we avoid auxiliary containers for the final result.

## My Original Solution

```cpp
class Solution {
public:
    string sortVowels(string s) {
        unordered_map<char,int> freqCount, firstIndex;
        for(int i = 0;i < s.size();i++){
            char c = s[i];
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                freqCount[c] += 1;
                if(firstIndex.find(c) == firstIndex.end()) firstIndex[c] = i;
            }
        }
        vector<char> vowel;
        for(auto i : firstIndex) vowel.push_back(i.first);
        sort(vowel.begin(), vowel.end() ,[&] (char a, char b){
            if(freqCount[a] == freqCount[b]) return firstIndex[a] < firstIndex[b];
            return freqCount[a] > freqCount[b];
        });
        int curr = 0;
        string result = s;
        for(int i = 0; i < result.size(); i++){
            char c = result[i];
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                result[i] = vowel[curr];
                freqCount[vowel[curr]]--;
                if(freqCount[vowel[curr]] == 0) curr++;
            }
        }
        return result;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    string sortVowels(string s) {
        const string V = "aeiou";
        const int INF = 1e9;
        int freq[26] = {0};
        int firstPos[26];
        fill(begin(firstPos), end(firstPos), -1);

        // 1️⃣ count frequencies & record first occurrence
        for (int i = 0; i < (int)s.size(); ++i) {
            char c = s[i];
            if (V.find(c) != string::npos) {
                ++freq[c - 'a'];
                if (firstPos[c - 'a'] == -1) firstPos[c - 'a'] = i;
            }
        }

        // 2️⃣ collect distinct vowels that appear
        vector<char> order;
        for (char c : V) {
            if (freq[c - 'a'] > 0) order.push_back(c);
        }

        // 3️⃣ sort by (freq desc, firstPos asc)
        sort(order.begin(), order.end(),
            [&](char a, char b) {
                if (freq[a - 'a'] != freq[b - 'a'])
                    return freq[a - 'a'] > freq[b - 'a'];
                return firstPos[a - 'a'] < firstPos[b - 'a'];
            });

        // 4️⃣ rebuild the string in‑place
        int idx = 0;                     // index in `order`
        for (char &c : s) {
            if (V.find(c) != string::npos) {
                c = order[idx];
                if (--freq[order[idx] - 'a'] == 0) ++idx;
            }
        }
        return s;
    }
};
```

## Code Walkthrough

- **Frequency & first position arrays** (`freq`, `firstPos`) replace the two hash maps; indexing by `c - 'a'` yields $O(1)$ access and keeps memory constant.  
- **`order` construction** iterates over the fixed vowel set, guaranteeing at most five elements.  
- **Custom comparator** directly encodes the problem’s sorting rule: `freq` descending, then `firstPos` ascending.  
- **In‑place replacement loop** uses a reference `char &c` so we modify `s` without allocating a new string. The `idx` pointer moves to the next vowel only when the current vowel’s remaining count drops to zero, ensuring the greedy placement respects the required ordering.
