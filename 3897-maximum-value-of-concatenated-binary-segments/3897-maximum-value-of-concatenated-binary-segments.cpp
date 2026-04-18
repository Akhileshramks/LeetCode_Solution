class Solution {
public:
    bool static comparator(pair<int,int> &a, pair<int,int>& b){
        if(a.second == 0 && b.second != 0) return true;
        else if(b.second == 0 && a.second != 0) return false;
        else if(a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    }

    int exponentiation_pow(long x,int n, int MOD){
        long res = 1;
        while(n > 0){
            if(n % 2 == 1){
                res = (res * x) % MOD;
                n -= 1;
            }else{
                x = (x * x) % MOD;
                n /= 2;
            }
        }
        return res;
    }
    int maxValue(vector<int>& nums1, vector<int>& nums0) {
        int MOD = 1e9 + 7;
        vector<pair<int,int>> binaryString;
        int n = nums1.size();
        for(int i = 0;i < n;i++){
            binaryString.push_back({nums1[i],nums0[i]});
        }
        sort(binaryString.begin(), binaryString.end(), comparator);
        int res = 0;
        for(int i = 0; i < n; i++){
            int a = binaryString[i].first;
            int b = binaryString[i].second;
            res = (1LL * res * exponentiation_pow(2, a, MOD)) % MOD;
            int mask = exponentiation_pow(2, a, MOD) - 1;
            res = (res + mask) % MOD;
            res = (1LL * res * exponentiation_pow(2, b, MOD)) % MOD;
        }
        return res;
    }
};