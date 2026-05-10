# 3926. Count Valid Word Occurrences

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** N/A &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 116 ms &nbsp;|&nbsp; **Memory:** 239.7 MB

---

## Problem

You are given an array of strings `chunks`. The strings are concatenated in order to form a single string `s`.

You are also given an array of strings `queries`.

A **word** is defined as a **substring** of `s` that:

	
- consists of lowercase English letters (`'a'` to `'z'`),
	
- may include hyphens (`'-'`) only if each hyphen is surrounded by lowercase English letters, and
	
- is not part of a longer substring that also satisfies the above conditions.

Any character that is not a lowercase English letter or a valid hyphen acts as a separator.

Return an integer array `ans` such that `ans[i]` is the number of occurrences of `queries[i]` as a word in `s`.

A **substring** is a contiguous **non-empty** sequence of characters within a string.

 

**Example 1:**

**Input:** chunks = ["hello wor","ld hello"], queries = ["hello","world","wor"]

**Output:** [2,1,0]

**Explanation:**

	
- Concatenating all strings in `chunks` gives `s = "hello world hello"`.
	
- The valid words in `s` are `"hello"` which appears twice and `"world"` which appears once.
	
- Thus, the `ans = [2, 1, 0]`.

**Example 2:**

**Input:** chunks = ["a--b a-","-c"], queries = ["a","b","c"]

**Output:** [2,1,1]

**Explanation:**

	
- Concatenating all strings in `chunks` gives `s = "a--b a--c"`.
	
- The valid words in `s` are `"a"` which appears twice, `"b"` which appears once, and `"c"` which appears once.
	
- Thus, the `ans = [2, 1, 1]`.

**Example 3:**

**Input:** chunks = ["hello"], queries = ["hello","ell"]

**Output:** [1,0]

**Explanation:**

	
- The valid word in `s` is `"hello"` which appears once.
	
- Thus, the `ans = [1, 0]`.

## Constraints

- `1 <= chunks.length <= 105`
	
- `1 <= chunks[i].length <= 105`​​​​​​​
	
- `chunks[i]` may consist of lowercase English letters, spaces, and hyphens.
	
- The total length of all strings in `chunks` does not exceed `105`
	
- `1 <= queries.length <= 105`
	
- `1 <= queries[i].length <= 105`​​​​​​​
	
- `queries[i]` is a valid word
	
- The total length of all strings in `queries` does not exceed `105`

## Hints

_No hints provided._

---

## Intuition  

The whole problem collapses to **tokenizing** a single string `s` under a very specific rule set.  
If we can decide in **O(1)** whether a character belongs to the current word, we can walk `s` once, extract every maximal valid word, and count them with a hash map.  
The “aha” moment is that a hyphen is *only* valid when both neighbours are lowercase letters, so the decision can be made locally using the previous and next characters—no back‑tracking or extra passes are required.

## Approach  

1. **Concatenate** all `chunks` into one string `s`.  
2. **Linear scan** `s` with an index `i`. Maintain a temporary string `cur`.  
   - If `s[i]` is a lowercase letter → append to `cur`.  
   - Else if `s[i]` is `'-'` **and** `i>0`, `i+1<|s|`, and both neighbours are letters → append to `cur`.  
   - Otherwise the character is a separator:  
     - If `cur` is non‑empty, increment `cnt[cur]` in an `unordered_map`.  
     - Reset `cur` to empty.  
3. After the loop, flush the last `cur` (if any) into the map.  
4. For each `queries[i]`, look up `cnt[queries[i]]` (default 0) and store the result.  

## Complexity Analysis  

|                | Complexity | Reason                                                                 |
|----------------|------------|------------------------------------------------------------------------|
| **Time**       | $O(N + Q)$ | $N$ = total length of `s` (≤ 10⁵) for one pass; $Q$ = total length of all queries for look‑ups |
| **Space**      | $O(U)$     | $U$ = number of distinct valid words (stored in the hash map)         |

## Key Takeaways  

- **Local hyphen validation** eliminates the need for a separate preprocessing step; a single pass suffices.  
- **Avoid counting empty tokens** by checking `cur.empty()` before updating the map.  
- Pre‑allocating the hash map (`reserve`) based on an upper bound (`N`) prevents costly rehashes under the tight time limit.  
- Concatenating `chunks` first is safe because the total length is bounded by $10^5$, keeping memory usage linear.

## My Original Solution

```cpp
class Solution {
public:
    bool isLower(char c){
        return 'a' <= c && c <= 'z';
    }
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {
        unordered_map<string,int> mpp;
        string s = "";
        for(auto i : chunks) s += i;
        int n = s.size();
        string word = "";
        for(int i = 0;i < n;i++){
            if(isLower(s[i]) || (s[i] == '-' && i - 1 >= 0 && isLower(s[i - 1]) && i + 1 < n && isLower(s[i+1]))) word += s[i];
            else{
                mpp[word]++;
                word = "";
            }
        }
        mpp[word]++;
        vector<int> res;
        for(auto m : queries) res.push_back(mpp[m]);
        return res;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    vector<int> countWordOccurrences(const vector<string>& chunks,
                                     const vector<string>& queries) {
        // 1) build the full string
        string s;
        s.reserve(100000);                     // total length ≤ 1e5
        for (const auto& part : chunks) s += part;

        // 2) count all valid words
        unordered_map<string, int> freq;
        freq.reserve(s.size());                // upper bound on distinct words

        auto isLetter = [](char c) { return 'a' <= c && c <= 'z'; };

        string cur;
        const int n = static_cast<int>(s.size());
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isLetter(c) ||
                (c == '-' && i > 0 && i + 1 < n && isLetter(s[i - 1]) && isLetter(s[i + 1]))) {
                cur.push_back(c);
            } else {
                if (!cur.empty()) {
                    ++freq[cur];
                    cur.clear();
                }
            }
        }
        if (!cur.empty()) ++freq[cur];         // flush the tail

        // 3) answer queries
        vector<int> ans;
        ans.reserve(queries.size());
        for (const auto& q : queries) ans.push_back(freq[q]); // default 0 if missing
        return ans;
    }
};
```

## Code Walkthrough  

- **`isLetter` lambda** isolates the character class test, making the main loop readable.  
- The **hyphen condition** `c == '-' && i > 0 && i + 1 < n && isLetter(s[i‑1]) && isLetter(s[i+1])` checks the two neighbours in **O(1)** time, guaranteeing that a hyphen is only kept when surrounded by letters.  
- Whenever a **separator** is hit, we only update the map if `cur` is non‑empty, thereby discarding empty tokens that would otherwise pollute the count.  
- After the loop, a final `if (!cur.empty())` flushes the last word, handling the case where the string ends with a valid word.  
- Query answers are retrieved directly from `freq`; the unordered map returns `0` for missing keys, satisfying the “word not present” case without extra conditionals.
