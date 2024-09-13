class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> prefix(n);
        int res = 0;
        for(int i=0;i<n;i++){
            res ^= arr[i];
            prefix[i] = res;
        }
        vector<int> result;
        for(auto i : queries){
            if(i[0]-1 >= 0){
                result.push_back(prefix[i[0]-1] ^ prefix[i[1]]);
            }
            else{
                result.push_back(prefix[i[1]]);
            }
        }
        return result;
    }
};