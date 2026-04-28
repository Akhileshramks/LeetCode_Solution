class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;
        int mod = grid[0][0] % x;;
        int n = grid.size(), m = grid[0].size();
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                nums.push_back(grid[i][j]);
                if(mod != grid[i][j] % x) return -1;  
            }
        }
        sort(nums.begin(), nums.end());
        n = nums.size();
        int median = nums[n/2];
        int res = 0;
        for(int i = 0;i < n;i++){
            res += abs(median - nums[i])/x;
        }
        return res;
    }
};