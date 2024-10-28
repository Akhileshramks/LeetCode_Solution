class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int l = 0;
        unordered_map<int,int> mpp;
        int maxi = 0;
        for(int r = 0;r < n;r++){
            if(mpp.find(s[r]-'a') != mpp.end()){
                l = max(l,mpp[s[r]-'a'] + 1);
            }
            mpp[s[r]-'a'] = r;
            maxi = max(maxi,r-l+1);
        }
        return maxi;
    }
};