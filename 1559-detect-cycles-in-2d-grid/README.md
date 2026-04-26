# 1559. Detect Cycles in 2D Grid

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix &nbsp;|&nbsp; **Solved:** April 26, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 19 ms &nbsp;|&nbsp; **Memory:** 73 MB

---

## Problem

Given a 2D array of characters `grid` of size `m x n`, you need to find if there exists any cycle consisting of the **same value** in `grid`.

A cycle is a path of **length 4 or more** in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the **same value** of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle `(1, 1) -> (1, 2) -> (1, 1)` is invalid because from `(1, 2)` we visited `(1, 1)` which was the last visited cell.

Return `true` if any cycle of the same value exists in `grid`, otherwise, return `false`.

 

**Example 1:**

**![](https://assets.leetcode.com/uploads/2020/07/15/1.png)**

> **Input:** grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
> **Output:** true
> **Explanation: **There are two valid cycles shown in different colors in the image below:
> ![](https://assets.leetcode.com/uploads/2020/07/15/11.png)

**Example 2:**

**![](https://assets.leetcode.com/uploads/2020/07/15/22.png)**

> **Input:** grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
> **Output:** true
> **Explanation: **There is only one valid cycle highlighted in the image below:
> ![](https://assets.leetcode.com/uploads/2020/07/15/2.png)

**Example 3:**

**![](https://assets.leetcode.com/uploads/2020/07/15/3.png)**

> **Input:** grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
> **Output:** false

## Constraints

- `m == grid.length`
	
- `n == grid[i].length`
	
- `1 <= m, n <= 500`
	
- `grid` consists only of lowercase English letters.

## Hints

1. Keep track of the parent (previous position) to avoid considering an invalid path.
2. Use DFS or BFS and keep track of visited cells to see if there is a cycle.

---

## Intuition

The grid can be seen as an undirected graph: each cell is a vertex, and edges exist between orthogonal neighbours that contain the **same character**.  
A cycle of length ≥ 4 exists **iff** during a depth‑first search we encounter a previously visited vertex that is **not** the immediate predecessor (parent) of the current vertex.  
The parent check eliminates the trivial back‑edge of length 2, and any other visited neighbour forces a closed loop that must contain at least four distinct cells because the DFS has already moved away from the start before the revisit.

## Approach

1. Iterate over every cell; start a DFS from any cell that has not been visited yet.  
2. In the recursive DFS `dfs(i, j, pi, pj)`  
   * Mark `(i, j)` as visited.  
   * For each of the four directions compute neighbour `(x, y)`.  
   * Skip out‑of‑bounds or cells with a different character.  
   * Skip the neighbour that is exactly the parent `(pi, pj)` – this is the move we just came from.  
   * If `(x, y)` is already visited → a cycle is found → return `true`.  
   * Otherwise recurse `dfs(x, y, i, j)`. If any recursive call returns `true`, propagate it upward.  
3. If any DFS reports a cycle, return `true`; otherwise, after scanning the whole grid, return `false`.

## Complexity Analysis

|               | Complexity | Reason                                                                 |
|---------------|------------|------------------------------------------------------------------------|
| **Time**      | $O(m \cdot n)$ | Each cell is visited once; each of its four edges is examined a constant number of times. |
| **Space**     | $O(m \cdot n)$ | `visited` matrix stores a flag per cell; recursion stack can grow to the size of the component (worst case $m\cdot n$). |

## Key Takeaways

- **Parent tracking** is essential in undirected cycle detection; without it the algorithm would mistake the immediate back‑track for a cycle.  
- The DFS condition `if (visited[x][y]) return true;` **automatically guarantees** a cycle length of at least 4 because the parent edge is excluded.  
- For grids up to $500 \times 500$, recursive DFS fits within typical stack limits, but an iterative stack or Union‑Find can be swapped in to avoid recursion depth issues.  
- Using a **single `visited` matrix** across all components prevents re‑exploration and yields linear time, even when many disconnected same‑character regions exist.

## My Original Solution

```cpp
class Solution {
public:
    bool isCycleDetect(vector<vector<char>>& grid, vector<vector<int>>& visited, int src_i, int src_j, int par_i, int par_j, int n, int m){
        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, -1, 1, 0};
        visited[src_i][src_j] = true;
        for(int i = 0;i < 4;i++){
            int x = src_i + dx[i];
            int y = src_j + dy[i];
            if(x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != grid[src_i][src_j] || (par_i == x && par_j == y)) continue;
            if(visited[x][y]) return true;
            if(isCycleDetect(grid, visited, x, y, src_i, src_j, n, m)) return true;
        }
        return false;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m, false));
        bool cycle = false;
        for(int i = 0;i < n;i++){
            for(int j = 0;j <m;j++){
                if(!visited[i][j]){
                    bool isCycle = isCycleDetect(grid, visited, i, j, -1, -1, n, m);
                    if(isCycle) return isCycle;
                }
            }
        }
        return false;
    }
};
```

## Professional Refactor

```cpp
// language: cpp
class Solution {
public:
    // Directions: up, left, right, down
    const int dx[4] = {-1, 0, 0, 1};
    const int dy[4] = {0, -1, 1, 0};

    // Depth‑first search that returns true as soon as a cycle is found.
    bool dfs(const vector<vector<char>>& grid,
             vector<vector<bool>>& visited,
             int i, int j,               // current cell
             int pi, int pj) {          // parent cell
        visited[i][j] = true;
        for (int dir = 0; dir < 4; ++dir) {
            int ni = i + dx[dir];
            int nj = j + dy[dir];

            // Boundary / character check
            if (ni < 0 || ni >= (int)grid.size() ||
                nj < 0 || nj >= (int)grid[0].size() ||
                grid[ni][nj] != grid[i][j])
                continue;

            // Skip the edge we just traversed
            if (ni == pi && nj == pj) continue;

            // Visited neighbour ≠ parent ⇒ cycle
            if (visited[ni][nj]) return true;

            // Recurse deeper
            if (dfs(grid, visited, ni, nj, i, j)) return true;
        }
        return false;
    }

    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j]) {
                    if (dfs(grid, visited, i, j, -1, -1))
                        return true;
                }
            }
        }
        return false;
    }
};
```

## Code Walkthrough

- **`dfs` signature** – receives the grid, the `visited` matrix, current coordinates `(i, j)`, and the parent coordinates `(pi, pj)`. The parent parameters let us differentiate a genuine back‑edge from the trivial one we just came from.  
- **Boundary / character guard** – `if (ni < 0 … || grid[ni][nj] != grid[i][j]) continue;` ensures we only walk on cells of the same letter.  
- **Parent skip** – `if (ni == pi && nj == pj) continue;` eliminates the immediate reverse move, which would otherwise be mistaken for a cycle of length 2.  
- **Cycle detection** – `if (visited[ni][nj]) return true;` is the core condition: encountering a previously visited cell that isn’t the parent closes a loop of length ≥ 4.  
- **Recursive descent** – the call `dfs(grid, visited, ni, nj, i, j)` propagates the current cell as the new parent. If any deeper call finds a cycle, the `true` bubbles up instantly, short‑circuiting the search.  
- **Outer loops** – the double `for` loop in `containsCycle` launches a fresh DFS from every unvisited component, guaranteeing that isolated regions are examined without redundant work.
