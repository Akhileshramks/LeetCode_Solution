class Solution {
public:
    char kthCharacter(int k) {
        int i = 1;
        string s = "a";
        while(i < k){
            int n = s.size();
            for(int i =0;i<n;i++){
                char m = s[i] == 'z' ? 'a' : s[i]+1;
                s += m;
            }
            i = i*2;
        }
        return s[k-1];
    }
};