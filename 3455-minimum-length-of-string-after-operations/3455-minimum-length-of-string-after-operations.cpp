class Solution {
public:
    int minimumLength(string s) {
        unordered_map<int,int> mpp;
        int n = s.size();
        for(int i = 0;i < n;i++){
            if(mpp[s[i]-'a'] > 1) mpp[s[i]-'a']--;
            else mpp[s[i]-'a']++;
        }
        int res = 0;
        for(int i=0;i<26;i++){
            res += mpp[i];
        }
        return res;
    }
};