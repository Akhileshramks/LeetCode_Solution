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