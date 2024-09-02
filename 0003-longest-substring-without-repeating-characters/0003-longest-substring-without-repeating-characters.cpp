class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<int,int> mpp;
        int n = s.size();
        int l =0,r = 0;
        int maxi =0;
        while(r<n){
            int c = s[r]-'a';
            if(mpp.find(c)!=mpp.end()){
                l = max(l,mpp[c]+1);
                mpp.erase(c);
            }
            mpp[c] = r;
            maxi = max(maxi,r-l+1);
            r++;
        }
        return maxi;
    }
};