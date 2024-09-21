class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> lps(n,0);
        int length = 0;
        for(int i = 1;i<n;i++){
            while(length > 0 && s[i] != s[length]){
                length = lps[length-1];
            }
            if(s[length] == s[i]) length++;
            lps[i] = length;
        }
        int m = lps[n-1];
        return s.substr(0,m);
    }
};

/*

b a b b b 
0 0 1 1 1

*/