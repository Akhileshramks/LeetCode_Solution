class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int,int> mpp;
        int n = nums.size();
        for(int i = 0;i < n;i++){
            for(int j = i+1;j < n;j++){
                mpp[nums[i] * nums[j]]++;
            }
        }
        int res = 0;
        for(auto prod : mpp){
            //cout<< prod.second << " "<< prod.first<<endl;
            res += prod.second*(prod.second - 1)/2;
        }
        return res*8;
    }
};

// ,12,12,24,24,24,48,48

// nC2
// n*(n-1) /  2!