# 48. Rotate Image

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Math, Matrix &nbsp;|&nbsp; **Solved:** May 4, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 0 ms &nbsp;|&nbsp; **Memory:** 10.2 MB

---

## Problem

You are given an `n x n` 2D `matrix` representing an image, rotate the image by **90** degrees (clockwise).

You have to rotate the image **in-place**, which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

 

**Example 1:**

![](https://assets.leetcode.com/uploads/2020/08/28/mat1.jpg)

> **Input:** matrix = [[1,2,3],[4,5,6],[7,8,9]]
> **Output:** [[7,4,1],[8,5,2],[9,6,3]]

**Example 2:**

![](https://assets.leetcode.com/uploads/2020/08/28/mat2.jpg)

> **Input:** matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
> **Output:** [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

## Constraints

- `n == matrix.length == matrix[i].length`
	
- `1 <= n <= 20`
	
- `-1000 <= matrix[i][j] <= 1000`

## Hints

_No hints provided._

---

## Intuition

Rotating a square matrix $90^\circ$ clockwise can be decomposed into two elementary, in‑place operations:  

1. **Transpose** – swap element $(i, j)$ with $(j, i)$ for all $i < j$. This mirrors the matrix across its main diagonal.  
2. **Horizontal flip** – reverse each row (or equivalently, swap column $j$ with column $n-1-j$). After the transpose, a row‑wise reversal exactly yields the clockwise rotation.

Recognizing that these two linear transformations compose to the desired rotation eliminates the need for any auxiliary matrix.

## Approach

1. **Transpose** the matrix in‑place by iterating over the upper‑triangular part ($i < j$) and swapping `matrix[i][j]` with `matrix[j][i]`.  
2. **Reverse** every row using `std::reverse`, which performs an in‑place horizontal flip.

The combination of the two steps produces the final rotated matrix.

## Complexity Analysis

|               | Complexity | Reason                                                                 |
|---------------|------------|------------------------------------------------------------------------|
| **Time**      | $O(n^2)$   | Both the transpose (nested loop over $\frac{n(n-1)}{2}$ pairs) and the row reversals (linear scan of $n$ rows each of length $n$) touch each element a constant number of times. |
| **Space**     | $O(1)$     | All swaps and reversals are performed in‑place; only a few loop indices are used. |

## Key Takeaways

- **Upper‑triangular swap**: Transposing in‑place requires touching only the elements above the main diagonal, preventing double‑swapping.  
- **Geometric decomposition**: A $90^\circ$ clockwise rotation = *transpose* + *horizontal flip*; the order matters (transpose first, then reverse rows).  
- **In‑place guarantee**: Both operations are linear‑time and constant‑space, satisfying the strict “no extra matrix” constraint.  
- **Reusable pattern**: The same two‑step technique can be adapted for counter‑clockwise rotation (transpose then reverse columns) or for 180° rotation (reverse rows then reverse columns).

## My Original Solution

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0;i<n;i++){
            for(int j =i+1;j<n;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(int i=0;i<n;i++){
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};
```

## Professional Refactor

```cpp
class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        const int n = static_cast<int>(matrix.size());

        // 1. Transpose the matrix (swap across the main diagonal)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 2. Reverse each row to achieve the clockwise rotation
        for (int i = 0; i < n; ++i) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
```

## Code Walkthrough

- **Transpose loop** (`for (int i = 0; i < n; ++i) …`):  
  Only iterates where `j > i`, ensuring each pair `(i, j)` is swapped exactly once. This mirrors the matrix across its main diagonal without extra storage.

- **Row reversal** (`std::reverse(matrix[i].begin(), matrix[i].end());`):  
  After transposition, reversing a row swaps column `j` with column `n‑1‑j`. The combination of the two steps results in the required $90^\circ$ clockwise rotation.
