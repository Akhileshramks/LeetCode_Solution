class Solution {
public:
    bool canBeValid(string s, string locked) {
        int leftBrack = 0,noOnes = 0,noZeros = 0;
        int n = locked.size();
        stack<int> openBracket,anyBracket;
        for(int i=0;i<n;i++){
            if(locked[i] == '0') anyBracket.push(i);
            else if(s[i] == '(') openBracket.push(i);
            else{
                if(!openBracket.empty()) openBracket.pop();
                else if(!anyBracket.empty()) anyBracket.pop();
                else return false;
            }
        }
        
        while(!openBracket.empty() && !anyBracket.empty() && openBracket.top() < anyBracket.top()){
            openBracket.pop();
            anyBracket.pop();
        }
        if(!openBracket.empty()) return false;
        return anyBracket.size()%2 == 0;
    }
};