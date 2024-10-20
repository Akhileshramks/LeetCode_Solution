class Solution {
public:
    bool checkValidString(string s) {
        int mini = 0,maxi = 0;
        for(auto &i : s){
            if(i == '(') mini++, maxi++;
            else if(i == ')') mini-- , maxi--;
            else  mini -= 1, maxi += 1;
            if(mini < 0) mini = 0;
            if(maxi < 0) return false;
        }
        return mini == 0;
    }
};