class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<int,int> mpp;
        int n = s.size();
        int l = 0,r = 0 , maxf = 0 , maxLen = 0;

        while(r < n){
            mpp[s[r]-'A']++;
            maxf = max(mpp[s[r]-'A'],maxf);
            while(r - l + 1 - maxf > k && l < r){
                mpp[s[l]-'A']--;
                l++;
            }
            maxLen = max(maxLen,r-l+1);
            r++;
        }
        return maxLen;
    }
};