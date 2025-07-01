class Solution {
public:
    int possibleStringCount(string word) {
        char lastChar = ' ';
        int ans = 1;
        for(char c : word){
            if(c == lastChar) ans++;
            lastChar = c;
        }
        return ans;
    }
};