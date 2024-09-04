class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        int l = 0, r = 0, minLen = INT_MAX, final_l = -1, cnt = 0;
        unordered_map<int,int> mpp;
        for(auto i : t){
            mpp[ i - 'A' ]++;
        }
        int tlen = t.size();
        while(r < n){
            if(mpp[ s[r]-'A' ] > 0) cnt++;
            mpp[ s[r]-'A' ]--;
            while(l<=r && cnt == tlen){
                if(r-l+1 < minLen){
                    minLen = r-l+1;
                    final_l = l;
                }
                mpp[s[l]-'A']++;
                if(mpp[s[l]-'A'] > 0) cnt--;
                l++;
            }
            r++;
        }
        if(final_l == -1) return "";
        return s.substr(final_l,minLen);
    }
};