class Solution {
public:
    int minAddToMakeValid(string s) {
        int ans = 0;
        int count = 0;
        for(char &i : s){
            if(i == '(') count++;
            else if(count > 0) count--;
            else ans++;
        }
        return ans + count;
    }
};