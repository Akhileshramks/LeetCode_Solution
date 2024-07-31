class Solution {
public:
    int solve(vector<vector<int>>& books, int shelfWidth, int idx, int currWidth, int currHeight, vector<vector<int>>& dp) {
        int n = books.size();
        
        if (idx == n) { 
            return currHeight;
        }
        
        if (dp[idx][currWidth] != -1) { 
            return dp[idx][currWidth];
        }
        
        int same = INT_MAX;
        if (books[idx][0] + currWidth <= shelfWidth) {
            same = solve(books, shelfWidth, idx + 1, books[idx][0] + currWidth, max(currHeight, books[idx][1]), dp);
        }
        
        int notsame = currHeight + solve(books, shelfWidth, idx + 1, books[idx][0], books[idx][1], dp); 
        
        return dp[idx][currWidth] = min(same, notsame);
    }

    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<vector<int>> dp(n+1, vector<int>(shelfWidth + 1, -1)); 
        return solve(books, shelfWidth, 0, 0, 0, dp);
    }
};