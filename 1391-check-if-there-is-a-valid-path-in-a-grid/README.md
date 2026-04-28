# 1391. Check if There is a Valid Path in a Grid

**Difficulty:** Medium &nbsp;|&nbsp; **Topics:** Array, Depth-First Search, Breadth-First Search, Union-Find, Matrix &nbsp;|&nbsp; **Solved:** April 28, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 56 ms &nbsp;|&nbsp; **Memory:** 62 MB

---

## Problem

You are given an `m x n` `grid`. Each cell of `grid` represents a street. The street of `grid[i][j]` can be:

	
- `1` which means a street connecting the left cell and the right cell.
	
- `2` which means a street connecting the upper cell and the lower cell.
	
- `3` which means a street connecting the left cell and the lower cell.
	
- `4` which means a street connecting the right cell and the lower cell.
	
- `5` which means a street connecting the left cell and the upper cell.
	
- `6` which means a street connecting the right cell and the upper cell.

![](https://assets.leetcode.com/uploads/2020/03/05/main.png)

You will initially start at the street of the upper-left cell `(0, 0)`. A valid path in the grid is a path that starts from the upper left cell `(0, 0)` and ends at the bottom-right cell `(m - 1, n - 1)`. **The path should only follow the streets**.

**Notice** that you are **not allowed** to change any street.

Return `true`_ if there is a valid path in the grid or _`false`_ otherwise_.

 

**Example 1:**

![](https://assets.leetcode.com/uploads/2020/03/05/e1.png)

> **Input:** grid = [[2,4,3],[6,5,2]]
> **Output:** true
> **Explanation:** As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).

**Example 2:**

![](https://assets.leetcode.com/uploads/2020/03/05/e2.png)

> **Input:** grid = [[1,2,1],[1,2,1]]
> **Output:** false
> **Explanation:** As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)

**Example 3:**

> **Input:** grid = [[1,1,2]]
> **Output:** false
> **Explanation:** You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).

## Constraints

- `m == grid.length`
	
- `n == grid[i].length`
	
- `1 <= m, n <= 300`
	
- `1 <= grid[i][j] <= 6`

## Hints

1. Start DFS from the node (0, 0) and follow the path till you stop.
2. When you reach a cell and cannot move anymore check that this cell is (m - 1, n - 1) or not.

---

## Intuition

The grid can be seen as a planar graph where each cell is a node and the street type determines which of its four sides have open connections.  
If two adjacent cells have *matching* openings (e.g., the right side of the left cell and the left side of the right cell are both present), they belong to the same connected component.  
Thus the problem reduces to **checking whether the start cell (0, 0) and the target cell (m‑1, n‑1) lie in the same component**.  
Union‑Find (Disjoint Set Union) is perfect for this because we can merge cells in *O(α(N))* time and later query connectivity in *O(α(N))* time, where *α* is the inverse Ackermann function.

The clever part is encoding each street type as a 4‑bit mask (`up, right, down, left`).  
A single bitwise‑and tells us whether a particular side is open, letting us test adjacency in constant time.

---

## Approach

1. **Pre‑compute side masks** for the six street types:  
   `mask[t]` is a 4‑bit integer where bit 0 = up, bit 1 = right, bit 2 = down, bit 3 = left.  
2. Initialise a Union‑Find structure for `N = m·n` cells.  
3. Iterate over every cell `(i, j)` and for each of the four directions `k ∈ {0,1,2,3}`  
   * compute neighbour `(ni, nj)`.  
   * If neighbour is inside the grid, check  
     `mask[grid[i][j]] & (1 << k)` **and** `mask[grid[ni][nj]] & (1 << ((k+2)%4))`.  
     When both bits are set, the two cells are mutually reachable → `union(idx(i,j), idx(ni,nj))`.  
4. After processing the whole grid, compare the representatives of the start and end cells.  
   If they are equal, a valid path exists.

---

## Complexity Analysis

|                | Complexity | Reason |
|----------------|------------|--------|
| **Time**       | $O(mn\cdot \alpha(mn))$ | Each of the $mn$ cells examines at most 4 neighbours; each `union`/`find` costs $α(N)$ amortised. |
| **Space**      | $O(mn)$    | Union‑Find stores two integer arrays of size $mn$; the mask array and direction vectors are $O(1)$. |

---

## Key Takeaways

- **Bitmask encoding** turns a multi‑case adjacency check into a single constant‑time operation.  
- Modeling the grid as an **undirected graph** and using Union‑Find avoids explicit BFS/DFS recursion depth issues for the maximal $300\times300$ grid.  
- The direction‑to‑bit mapping (`k` ↔ `((k+2)%4)`) is a reusable pattern when dealing with bidirectional connectivity on a lattice.  
- Converting a 2‑D coordinate to a 1‑D index (`i*m + j`) lets Union‑Find operate on a flat array, simplifying implementation and improving cache locality.

---

## My Original Solution

```cpp
class UnionFind{
    public:
        vector<int> parent;
        vector<int> size;

        UnionFind(int n){
            parent.resize(n);
            size.resize(n);
            for(int i = 0;i < n;i++){
                parent[i] = i;
                size[i] = 1;
            }
        }

        int findParent(int i){
            if(parent[i] == i) return i;
            return parent[i] = findParent(parent[i]);
        }

        void merge(int i, int j){
            int ul_i = findParent(i);
            int ul_j = findParent(j);
            if(ul_i == ul_j) return;
            if(size[ul_i] >= size[ul_j]){
                parent[ul_j] = ul_i;
                size[ul_i] += size[ul_j]; 
            }else{
                parent[ul_i] = ul_j;
                size[ul_j] += size[ul_i]; 
            }
            return;
        }
};
class Solution {
public:
    int convert2dtod(int i, int j, int m){
        return i * m + j;
    }
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    bool hasValidPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionFind graph(n*m);
        vector<int> state = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
        vector<pair<int,int>> steps = {{-1,0}, {0,1}, {1, 0}, {0,-1}};
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                for(int k = 0;k < 4;k++){
                    int dx = i + steps[k].first;
                    int dy = j + steps[k].second;
                    int currState = state[grid[i][j]];
                    if(isValid(dx, dy, n, m)){
                        int nextState = state[grid[dx][dy]];
                        int currRoad = currState & (1 << k);
                        int nextRoad = nextState & (1 << ((k + 2) % 4));
                        if(currRoad && nextRoad) graph.merge(convert2dtod(i, j, m), convert2dtod(dx, dy, m));
                    }
                }
            }
        }

        return graph.findParent(convert2dtod(0, 0, m)) == graph.findParent(convert2dtod(n - 1, m - 1, m));
    }
};
```

## Professional Refactor

```cpp
// 1391. Check if There is a Valid Path in a Grid
// Union‑Find + bitmask adjacency, O(mn α(mn)) time, O(mn) space.

class DSU {
public:
    DSU(int N) : parent(N), sz(N, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
private:
    vector<int> parent, sz;
};

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        const int m = grid[0].size(), n = grid.size();
        DSU dsu(n * m);

        // bitmask: up(0), right(1), down(2), left(3)
        const int mask[7] = {
            0,          // placeholder
            0b1010,     // 1: left‑right
            0b0101,     // 2: up‑down
            0b1100,     // 3: left‑down
            0b0110,     // 4: right‑down
            0b1001,     // 5: left‑up
            0b0011      // 6: right‑up
        };

        const int dr[4] = {-1, 0, 1, 0};
        const int dc[4] = {0, 1, 0, -1};

        auto idx = [&](int r, int c) { return r * m + c; };

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                int curMask = mask[grid[r][c]];
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                    int nxtMask = mask[grid[nr][nc]];
                    // check current side k and opposite side (k+2)%4
                    if ( (curMask & (1 << k)) && (nxtMask & (1 << ((k + 2) % 4))) )
                        dsu.unite(idx(r, c), idx(nr, nc));
                }
            }
        }
        return dsu.find(idx(0, 0)) == dsu.find(idx(n - 1, m - 1));
    }
};
```

## Code Walkthrough

- **`mask[7]`** – encodes the four possible openings for each street type as a 4‑bit integer (`up, right, down, left`).  
- **Direction arrays `dr` / `dc`** – standard lattice offsets; the opposite direction of `k` is `(k+2)%4`.  
- **Neighbour test**:  
  ```cpp
  if ( (curMask & (1 << k)) && (nxtMask & (1 << ((k + 2) % 4))) )
      dsu.unite(idx(r, c), idx(nr, nc));
  ```  
  The first bitwise‑and checks whether the current cell has an opening towards the neighbour; the second ensures the neighbour opens back.  
- **Union‑Find**: `dsu.unite` merges the two cell indices; path compression and union by size keep operations near‑constant.  
- **Final check**: connectivity of the start (`(0,0)`) and end (`(n‑1,m‑1)`) cells determines the answer.
