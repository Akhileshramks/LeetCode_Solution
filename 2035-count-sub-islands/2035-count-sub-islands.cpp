class Solution {
    // Directions in which we can traverse inside the grids.
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Helper method to check if the cell at the position (x, y) in the 'grid'
    // is a land cell.
    bool isCellLand(int x, int y, vector<vector<int>>& grid) {
        return grid[x][y] == 1;
    }

    // Traverse all cells of island starting at position (x, y) in 'grid2',
    // and check this island is a sub-island in 'grid1'.
    bool isSubIsland(int x, int y, vector<vector<int>>& grid1,
                     vector<vector<int>>& grid2,
                     vector<vector<bool>>& visited) {
        int totalRows = grid2.size();
        int totalCols = grid2[0].size();
        // Traverse on all cells using the depth-first search method.
        bool isSubIsLand = true;

        // If the current cell is not a land cell in 'grid1', then the current
        // island can't be a sub-island.
        if (!isCellLand(x, y, grid1)) {
            isSubIsLand = false;
        }

        // Traverse on all adjacent cells.
        for (auto& direction : directions) {
            int nextX = x + direction[0];
            int nextY = y + direction[1];
            // If the next cell is inside the 'grid2', is never visited and is a
            // land cell, then we traverse to the next cell.
            if (nextX >= 0 && nextY >= 0 && nextX < totalRows &&
                nextY < totalCols && !visited[nextX][nextY] &&
                isCellLand(nextX, nextY, grid2)) {
                // Push the next cell in the recursive stack and mark it as
                // visited.
                visited[nextX][nextY] = true;
                bool nextCellIsPartOfSubIsland =
                    isSubIsland(nextX, nextY, grid1, grid2, visited);
                isSubIsLand = isSubIsLand && nextCellIsPartOfSubIsland;
            }
        }
        return isSubIsLand;
    }

public:
    int countSubIslands(vector<vector<int>>& grid1,
                        vector<vector<int>>& grid2) {
        int totalRows = grid2.size();
        int totalCols = grid2[0].size();

        vector<vector<bool>> visited(totalRows, vector<bool>(totalCols, false));
        int subIslandCounts = 0;

        // Iterate on each cell in 'grid2'
        for (int x = 0; x < totalRows; ++x) {
            for (int y = 0; y < totalCols; ++y) {
                // If cell at the position (x, y) in the 'grid2' is not visited,
                // is a land cell in 'grid2',
                // and the island starting from this cell is a sub-island in
                // 'grid1', then we increment the count of sub-islands.
                if (!visited[x][y] && isCellLand(x, y, grid2)) {
                    visited[x][y] = true;
                    if (isSubIsland(x, y, grid1, grid2, visited)) {
                        subIslandCounts += 1;
                    }
                }
            }
        }
        // Return total count of sub-islands.
        return subIslandCounts;
    }
};