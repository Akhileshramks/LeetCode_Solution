class Solution {
public:
    bool checkValidString(string s) {
        int l = 0,star = 0;
        for(char i : s){
            if(i == '(') l++;
            else if(i == '*') star++;
            else if(i == ')'){
                if(l>0) l--;
                else if(star>0) star--;
                else return false;
            }
        }
        reverse(s.begin(),s.end());
        l=0,star=0;
        for(char i : s){
            if(i == ')') l++;
            else if(i == '*') star++;
            else if(i == '('){
                if(l>0) l--;
                else if(star>0) star--;
                else return false;
            }
        }
        return true;
    }
};