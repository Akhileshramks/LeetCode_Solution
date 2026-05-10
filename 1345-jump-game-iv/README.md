# 1345. Jump Game IV

**Difficulty:** Hard &nbsp;|&nbsp; **Topics:** Array, Hash Table, Breadth-First Search &nbsp;|&nbsp; **Solved:** May 10, 2026
**Language:** cpp &nbsp;|&nbsp; **Runtime:** 68 ms &nbsp;|&nbsp; **Memory:** 75 MB

---

## Problem

Given an array of integers `arr`, you are initially positioned at the first index of the array.

In one step you can jump from index `i` to index:

	
- `i + 1` where: `i + 1 < arr.length`.
	
- `i - 1` where: `i - 1 >= 0`.
	
- `j` where: `arr[i] == arr[j]` and `i != j`.

Return _the minimum number of steps_ to reach the **last index** of the array.

Notice that you can not jump outside of the array at any time.

 

**Example 1:**

> **Input:** arr = [100,-23,-23,404,100,23,23,23,3,404]
> **Output:** 3
> **Explanation:** You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.

**Example 2:**

> **Input:** arr = [7]
> **Output:** 0
> **Explanation:** Start index is the last index. You do not need to jump.

**Example 3:**

> **Input:** arr = [7,6,9,6,9,6,9,7]
> **Output:** 1
> **Explanation:** You can jump directly from index 0 to index 7 which is last index of the array.

## Constraints

- `1 <= arr.length <= 5 * 104`
	
- `-108 <= arr[i] <= 108`

## Hints

1. Build a graph of n nodes where nodes are the indices of the array and edges for node i are nodes i+1, i-1, j where arr[i] == arr[j].
2. Start bfs from node 0 and keep distance. The answer is the distance when you reach node n-1.

---

## Intuition  

The array can be seen as an **unweighted graph**: each index is a node, and from node *i* we can move to *i‑1*, *i+1*, or to **any** other index *j* with the same value `arr[i] == arr[j]`.  
The shortest‑path problem on an unweighted graph is solved by **Breadth‑First Search (BFS)**.  
The crucial observation is that all indices sharing the same value form a *complete subgraph* – we can “teleport” between them in a single step. By storing, for each distinct value, the list of its positions, we can expand this whole subgraph in **O(k)** where *k* is the number of occurrences, and then **discard** the list (clear it) so we never revisit those edges again. This prevents the naïve $O(n^2)$ blow‑up.

---

## Approach  

1. **Pre‑process**:  
   *Create a hash map* `pos[value] → vector of indices` so that all equal‑value jumps are reachable in $O(1)$ time.  

2. **BFS initialization**:  
   *Queue* `q` holds the current frontier, start with index 0.  
   `visited[i]` marks whether index *i* has been enqueued.  
   `steps` counts BFS layers (the number of jumps taken so far).  

3. **Layered expansion** (standard BFS):  
   * While `q` is not empty:  
     * Process all nodes in the current layer (`size = q.size()`).  
     * For each node `cur`:  
       - If `cur == n‑1` → return `steps`.  
       - Push `cur‑1` and `cur+1` if they are inside bounds and unvisited.  
       - Iterate over `pos[arr[cur]]` (all same‑value indices).  
         • Enqueue each unvisited index.  
       - **Clear** `pos[arr[cur]]` to avoid revisiting this value later.  

4. Increment `steps` after finishing a layer.  

The first time we reach the last index we have used the minimal number of jumps because BFS explores states in increasing distance order.

---

## Complexity Analysis  

|               | Complexity | Reason |
|---|---|---|
| **Time**  | $O(n)$ | Each index is enqueued at most once; the total work of iterating over all `pos[value]` lists is $\sum\limits_{v} |pos[v]| = n$. |
| **Space** | $O(n)$ | `visited` array, BFS queue, and the hash map together store at most $n$ indices. |

---

## Key Takeaways  

* **BFS on implicit graphs**: When moves are defined by index arithmetic and value‑based jumps, treat the problem as a shortest‑path search on a graph rather than trying greedy jumps.  
* **Value‑bucket trick**: Grouping equal values into a hash‑map gives $O(1)$ access to all “teleport” edges and collapses many potential edges into a single list.  
* **Clear after use**: Deleting (`clear()`) the bucket after its first expansion guarantees linear total work; otherwise the same bucket would be scanned repeatedly, leading to $O(n^2)$.  
* **Early exit**: Because BFS expands by layers, returning as soon as the target index is dequeued yields the optimal answer without extra distance bookkeeping.

---

## My Original Solution

```cpp
class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n, false);
        int count = 0;
        visited[0] = true;
        queue<int> q;
        q.push(0);
        unordered_map<int,vector<int>> mpp;
        for(int i = 0;i < n;i++) mpp[nums[i]].push_back(i);
        while(!q.empty()){
            int j = q.size();
            while(j--){
                int k = q.front();
                if(k == n - 1) return count;
                q.pop();
                int left = k - 1;
                int right = k + 1;
                if(left >= 0 && !visited[left]) q.push(left), visited[left] = true;
                if(right < n && !visited[right]) q.push(right), visited[right] = true;
                for(int i : mpp[nums[k]]){
                    if(!visited[i]){
                        q.push(i), visited[i] = true;
                    }
                }
                mpp[nums[k]].clear();
            }
            count++;
        }
        return 0;
    }
};
```

## Professional Refactor

```cpp
// 1345. Jump Game IV  —  BFS + value buckets
class Solution {
public:
    int minJumps(vector<int>& arr) {
        const int n = static_cast<int>(arr.size());
        if (n == 1) return 0;

        // value → all indices having that value
        unordered_map<int, vector<int>> buckets;
        for (int i = 0; i < n; ++i) {
            buckets[arr[i]].push_back(i);
        }

        vector<char> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        int steps = 0;

        while (!q.empty()) {
            int layerSize = q.size();
            while (layerSize--) {
                int cur = q.front(); q.pop();
                if (cur == n - 1) return steps;

                // neighbour: cur‑1
                if (cur - 1 >= 0 && !visited[cur - 1]) {
                    visited[cur - 1] = true;
                    q.push(cur - 1);
                }
                // neighbour: cur+1
                if (cur + 1 < n && !visited[cur + 1]) {
                    visited[cur + 1] = true;
                    q.push(cur + 1);
                }
                // neighbours with the same value
                for (int nxt : buckets[arr[cur]]) {
                    if (!visited[nxt]) {
                        visited[nxt] = true;
                        q.push(nxt);
                    }
                }
                // bucket no longer needed – prevents O(n²) rescans
                buckets[arr[cur]].clear();
            }
            ++steps;
        }
        return -1; // unreachable (should never happen with given constraints)
    }
};
```

## Code Walkthrough  

* **Bucket construction** (`buckets[arr[i]].push_back(i)`) – O($n$) preprocessing that lets us retrieve *all* equal‑value jumps in constant time per value.  
* **BFS loop** – `while (!q.empty())` processes the graph level by level; `steps` is incremented only after a whole layer is exhausted, guaranteeing that the first time we pop the last index we have used the minimum number of jumps.  
* **Same‑value expansion** – the `for (int nxt : buckets[arr[cur]])` loop enqueues every index sharing the current value. Immediately after, `buckets[arr[cur]].clear();` discards the list, ensuring each bucket contributes work only once.  
* **Visited guard** – `visited` prevents re‑adding already explored indices, which is essential because the graph contains many parallel edges (e.g., both `i‑1` and a same‑value jump could lead to the same node).  

This refactor keeps the original algorithmic idea intact while improving readability, adding safety checks, and documenting the reasoning behind each step.
