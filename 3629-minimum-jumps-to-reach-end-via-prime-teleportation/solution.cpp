const int N = 1e6 + 5;
vector<vector<int>> factors(1e6+5);
bool initialized = []() {
    for(int i = 2; i < N; i++){
        if(factors[i].size() != 0) continue;
        for(int j = i; j < N; j += i){
            factors[j].push_back(i);
        }
    }
    return true;
}();
class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        queue<int> q;
        q.push(0);
        int count = 0;
        vector<bool> visited(n, false);
        visited[0] = true;
        unordered_map<int, vector<int>> mpp;
        int maxElement = *max_element(nums.begin(), nums.end());
        for(int i = 0;i < n;i++){
            for(int j : factors[nums[i]]){
                mpp[j].push_back(i);
            }
        }
        while(!q.empty()){
            int j = q.size();
            while(j--){
                int k = q.front();
                q.pop();
                if(k == n - 1) return count;
                int left = k - 1;
                int right = k + 1;
                if(left >= 0 && !visited[left]){
                    visited[left] = true;
                    q.push(left);
                }

                if(right < n && !visited[right]){
                    visited[right] = true;
                    q.push(right);
                }
                
                if(factors[nums[k]].size() == 1){
                    for(int i : mpp[nums[k]]){
                        if(i != k && !visited[i]){
                            q.push(i);
                            visited[i] = true;
                        }
                    }
                    mpp[nums[k]].clear();
                }
            }
            count++;
        }
        return -1;
    }
};