class Solution {
public:
    string rotate(string s){
        return s.substr(s.size()-1,1)+s.substr(0,s.size()-1);
    }
    bool rotateString(string s, string goal) {
        int n = goal.size();
        if(s == goal) return true;
        for(int i = 0;i < n;i++){
            goal = rotate(goal);
            if(goal == s) return true;
        }
        return false;
    }
};