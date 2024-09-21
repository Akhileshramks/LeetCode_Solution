class Solution {
public:
    string lds(string s,int n){
        unordered_set<long long> currHash;
        long long base = 31;
        long long MOD = 1e11 + 7;
        long long hash = 0;
        long long power = 1;
        for(int k = 0;k<n-1;k++) power = (power*base*1LL)%MOD;
        for(int i =0;i<n;i++){
            hash = ((hash*base*1LL)%MOD + s[i]-'a' + 1) % MOD;
        }
        int m = s.size();
        for(int i = 0;i<=m-n;i++){
            if(currHash.find(hash) == currHash.end()) currHash.insert(hash); 
            else return s.substr(i,n);
            hash = ((hash - ((s[i]-'a'+1)*power*1LL))*base*1ll)%MOD;
            hash = (hash + (s[i+n]-'a' + 1))%MOD;
            hash = (hash + MOD) % MOD;
        }
        return "";
    }
    string longestDupSubstring(string s) {
        int n = s.size();
        int low = 0;
        int high = n;
        string res,ans;
        int mid;
        while(low <= high){
            mid = low + (high - low)/2;
            res = lds(s,mid);
            if(res != ""){
                ans = res;
                low = mid+1;
            } 
            else high = mid-1;
        }
        cout<< mid;
        return ans;
    }

};

/*

BANANA - 6

ANA - 3
*/