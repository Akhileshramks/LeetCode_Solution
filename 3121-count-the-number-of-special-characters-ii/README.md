# 3121. Count the Number of Special Characters II

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Hash Table, String &nbsp;|&nbsp; **Solved:** May 27, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 69 ms &nbsp;|&nbsp; **Memory:** 23882.8 MB

---

## Problem

You are given a string `word`. A letter `c` is called **special** if it appears **both** in lowercase and uppercase in `word`, and **every** lowercase occurrence of `c` appears before the **first** uppercase occurrence of `c`.

Return the number of_ _**special** letters_ _in_ _`word`.

 

**Example 1:**

**Input:** word = "aaAbcBC"

**Output:** 3

**Explanation:**

The special characters are `'a'`, `'b'`, and `'c'`.

**Example 2:**

**Input:** word = "abc"

**Output:** 0

**Explanation:**

There are no special characters in `word`.

**Example 3:**

**Input:** word = "AbBCab"

**Output:** 0

**Explanation:**

There are no special characters in `word`.

## Constraints

- `1 <= word.length <= 2 * 105`
	
- `word` consists of only lowercase and uppercase English letters.

## Hints

1. For each character `c`, store the first occurrence of its uppercase and the last occurrence of its lowercase.

---

## Intuition

The fundamental insight that makes this solution possible is recognizing that a character is special only if its lowercase version appears before its uppercase version in the string. This can be achieved by tracking the first occurrence of each lowercase and uppercase letter. The choice of using a vector to store these indices is due to the fixed number of letters in the alphabet, allowing for efficient lookup and update of indices.

## Approach

1. Initialize two vectors, `lowerInd` and `upperInd`, to store the indices of the first occurrence of each lowercase and uppercase letter, respectively. 
2. Iterate through the string, updating the indices in `lowerInd` and `upperInd` as we encounter each letter.

## Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n)$ | The algorithm iterates through the string of length $n$ once to update the indices, and then iterates through the alphabet (size 26) to count special characters. |
| **Space** | $O(1)$ | The space complexity is constant because the size of the vectors `lowerInd` and `upperInd` is fixed (26), regardless of the input size $n$. |

## Key Takeaways

* The use of separate vectors for tracking the indices of lowercase and uppercase letters simplifies the logic for determining special characters.
* Initializing the vectors with `INT_MAX` and `INT_MIN` allows for efficient comparison to determine if a character has been encountered before.
* The algorithm's efficiency comes from only needing to make a single pass through the input string to gather all necessary information.

## My Original Solution

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> lowerInd(26, INT_MAX), upperInd(26, INT_MIN);
        int n = word.size();
        int count = 0;
        for(int i = 0;i < n;i++){
            if(word[i] >= 'a' && word[i] <= 'z') lowerInd[word[i] - 'a'] = i;
            else if(word[i] >= 'A' && word[i] <= 'Z' && upperInd[word[i] - 'A'] == INT_MIN) upperInd[word[i] - 'A'] = i;
        }
        for(int i = 0;i < 26;i++){
            if(lowerInd[i] < upperInd[i] && lowerInd[i] != INT_MAX && upperInd[i] != INT_MIN) count++;
        }
        return count;
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    int numberOfSpecialChars(string word) {
        // Initialize vectors to store indices of first occurrence of each letter
        vector<int> lowerCaseIndices(26, INT_MAX);
        vector<int> upperCaseIndices(26, INT_MIN);
        
        // Iterate through the word to update indices
        for (int i = 0; i < word.size(); ++i) {
            char c = word[i];
            if (c >= 'a' && c <= 'z') {
                // Update index for lowercase letter if not already updated
                lowerCaseIndices[c - 'a'] = min(lowerCaseIndices[c - 'a'], i);
            } else if (c >= 'A' && c <= 'Z' && upperCaseIndices[c - 'A'] == INT_MIN) {
                // Update index for uppercase letter only if it's the first occurrence
                upperCaseIndices[c - 'A'] = i;
            }
        }
        
        // Count special characters
        int specialCount = 0;
        for (int i = 0; i < 26; ++i) {
            if (lowerCaseIndices[i] < upperCaseIndices[i] && lowerCaseIndices[i] != INT_MAX && upperCaseIndices[i] != INT_MIN) {
                specialCount++;
            }
        }
        
        return specialCount;
    }
};
```

## Code Walkthrough

The key transformation is in how we update the `lowerInd` and `upperInd` vectors. For each character in the string, we check if it's a lowercase or uppercase letter and update the corresponding index in the vectors. We only update the index for an uppercase letter if it's the first occurrence (i.e., its current index is `INT_MIN`). This ensures that we're comparing the first occurrence of each lowercase letter with the first occurrence of its corresponding uppercase letter.
