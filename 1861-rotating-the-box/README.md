# 1861. Rotating the Box

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Two Pointers, Matrix &nbsp;|&nbsp; **Solved:** May 6, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 23 ms &nbsp;|&nbsp; **Memory:** 65.2 MB

---

## Problem

You are given an `m x n` matrix of characters `boxGrid` representing a side-view of a box. Each cell of the box is one of the following:

	
- A stone `'#'`
	
- A stationary obstacle `'*'`
	
- Empty `'.'`

The box is rotated **90 degrees clockwise**, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity **does not** affect the obstacles' positions, and the inertia from the box's rotation **does not **affect the stones' horizontal positions.

It is **guaranteed** that each stone in `boxGrid` rests on an obstacle, another stone, or the bottom of the box.

Return _an _`n x m`_ matrix representing the box after the rotation described above_.

 

**Example 1:**

![](https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcodewithstones.png)

> **Input:** boxGrid = [["#",".","#"]]
> **Output:** [["."],
>          ["#"],
>          ["#"]]

**Example 2:**

![](https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcode2withstones.png)

> **Input:** boxGrid = [["#",".","*","."],
>               ["#","#","*","."]]
> **Output:** [["#","."],
>          ["#","#"],
>          ["*","*"],
>          [".","."]]

**Example 3:**

![](https://assets.leetcode.com/uploads/2021/04/08/rotatingtheboxleetcode3withstone.png)

> **Input:** boxGrid = [["#","#","*",".","*","."],
>               ["#","#","#","*",".","."],
>               ["#","#","#",".","#","."]]
> **Output:** [[".","#","#"],
>          [".","#","#"],
>          ["#","#","*"],
>          ["#","*","."],
>          ["#",".","*"],
>          ["#",".","."]]

## Constraints

- `m == boxGrid.length`
	
- `n == boxGrid[i].length`
	
- `1 <= m, n <= 500`
	
- `boxGrid[i][j]` is either `'#'`, `'*'`, or `'.'`.

## Hints

1. Rotate the box using the relation rotatedBox[i][j] = box[m - 1 - j][i].
2. Start iterating from the bottom of the box and for each empty cell check if there is any stone above it with no obstacles between them.

---

## Intuition

The stones only move **downward** after the rotation, which in the original orientation means they slide **rightward** until they hit an obstacle `'*'` or the row’s end.  
If we first let every stone “fall” within its own row, the rotation becomes a simple index transposition.  
The key insight is to treat each obstacle as a **reset point** for a greedy placement: count how many `'#'` appear between two obstacles (or between an obstacle and the row boundary), then fill those positions from right to left with exactly that many stones. This two‑pass scan resolves the gravity effect in $O(n)$ per row without extra data structures.

---

## Approach

1. **Process each row independently**  
   *First pass (left → right)* – keep a running counter `cnt` of stones. When we encounter `'*'` or the last column, store `cnt` at that index (it represents how many stones belong to the segment ending there) and reset `cnt`.  
   *Second pass (right → left)* – use the stored counts to place stones:  
   - If the cell is `'*'`, refresh the current segment’s remaining count.  
   - Otherwise, if the segment still has stones (`cnt > 0`), write `'#'` and decrement `cnt`; else write `'.'`.  

   The row now reflects the state **after gravity** but **before rotation**.

2. **Rotate the processed matrix**  
   The box is rotated $90^\circ$ clockwise, so a cell originally at `(i, j)` moves to `(j, m‑1‑i)` where `m` is the original number of columns.  
   Allocate an `n × m` result matrix filled with `'.'` and copy each processed row into its rotated coordinates.

3. **Return the rotated matrix**.

---

## Complexity Analysis

|               | Complexity | Reason                                                            |
|---------------|------------|-------------------------------------------------------------------|
| **Time**      | $O(m \cdot n)$ | Each of the $m$ rows is scanned twice (two passes) and then written once during rotation. |
| **Space**     | $O(m \cdot n)$ | Output matrix of size $n \times m$ plus $O(n)$ auxiliary array for a single row. |

---

## Key Takeaways

- **Separate concerns**: resolve gravity in the original orientation first, then rotate—avoids intertwining two orthogonal operations.  
- **Obstacles as segment delimiters**: treating `'*'` as a reset point lets a greedy left‑to‑right count be reused right‑to‑left for exact placement.  
- **Two‑pass linear scan** achieves $O(1)$ extra work per cell; no need for stacks or additional containers.  
- **Index mapping for rotation** (`(i, j) → (j, m‑1‑i)`) provides an in‑place‑style copy without an explicit transpose step.

---

## My Original Solution

```cpp
class Solution {
public:
    vector<char> changeColumnWise(vector<char> row){
        int n = row.size();
        vector<int> ans(n , 0);
        int count = 0;
        for(int i = 0;i < n;i++){
            if(row[i] == '#') count++;
            if(row[i] == '*' || i == n - 1){
                ans[i] = count;
                count = 0;
            }
        }
        count = ans[n-1];
        for(int i = n - 1;i >= 0;i--){
            if(row[i] == '*') count = ans[i];
            else if(count > 0){
                row[i] = '#';
                count--;
            }
            else row[i] = '.';
        }
        return row;
    }
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size();
        int m = boxGrid[0].size();
        vector<vector<char>> result(m, vector<char>(n, '.'));
        for(int i = 0;i < n;i++){
            vector<char> res = changeColumnWise(boxGrid[i]);
            for(int j = 0;j < m;j++){
                result[j][n - i - 1] = res[j];
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
    // Apply gravity to a single row: stones fall to the right until an obstacle or the edge.
    static vector<char> applyGravity(const vector<char>& row) {
        const int n = static_cast<int>(row.size());
        vector<int> stonesInSegment(n, 0);   // stones count for the segment ending at each index
        int cnt = 0;

        // First pass: count stones between obstacles / right border.
        for (int i = 0; i < n; ++i) {
            if (row[i] == '#') ++cnt;
            if (row[i] == '*' || i == n - 1) {
                stonesInSegment[i] = cnt;
                cnt = 0;                     // reset for the next segment
            }
        }

        // Second pass: fill from right to left using the stored counts.
        vector<char> res(row);
        cnt = stonesInSegment[n - 1];
        for (int i = n - 1; i >= 0; --i) {
            if (row[i] == '*') {
                cnt = stonesInSegment[i];    // start a new segment
                res[i] = '*';
            } else if (cnt > 0) {
                res[i] = '#';
                --cnt;
            } else {
                res[i] = '.';
            }
        }
        return res;
    }

    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        const int m = static_cast<int>(boxGrid.size());          // rows
        const int n = static_cast<int>(boxGrid[0].size());       // cols

        // Result after rotation: n rows, m columns.
        vector<vector<char>> rotated(n, vector<char>(m, '.'));

        for (int i = 0; i < m; ++i) {
            vector<char> settledRow = applyGravity(boxGrid[i]);
            for (int j = 0; j < n; ++j) {
                // Clockwise rotation: (i, j) → (j, m-1-i)
                rotated[j][m - 1 - i] = settledRow[j];
            }
        }
        return rotated;
    }
};
```

## Code Walkthrough

- **`applyGravity`**  
  1. **First pass** (`left → right`):  
     - `cnt` accumulates `'#'`.  
     - When we hit `'*'` or the last column, we store `cnt` at that index (`stonesInSegment[i]`) and reset `cnt`.  
     This partitions the row into independent segments delimited by obstacles.  

  2. **Second pass** (`right → left`):  
     - `cnt` is re‑initialized with the count belonging to the right‑most segment.  
     - If the current cell is an obstacle, we refresh `cnt` with the pre‑computed count for the new segment.  
     - Otherwise we place a stone while `cnt > 0`; when `cnt` is exhausted we write `'.'`.  

  The resulting `res` is the row after all stones have fallen to the right.

- **`rotateTheBox`**  
  - Allocate `rotated` of size `n × m` filled with `'.'`.  
  - For each original row `i`, obtain its gravity‑settled version `settledRow`.  
  - Map each column `j` to its rotated position using the formula `(j, m‑1‑i)`.  
  - Copy the character, completing the $90^\circ$ clockwise rotation in a single nested loop.
