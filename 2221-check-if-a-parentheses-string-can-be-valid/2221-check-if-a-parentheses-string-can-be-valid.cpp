class Solution {
public:
    bool canBeValid(string s, string locked) {

        int n = locked.size();
        if (n % 2 == 1) {
            return false;
        }
        int openBracket = 0,anyBracket = 0;
        for(int i=0;i<n;i++){
            if(locked[i] == '0') anyBracket++;
            else if(s[i] == '(') openBracket++;
            else{
                if(openBracket) openBracket--;
                else if(anyBracket) anyBracket--;
                else return false;
            }
        }
        
        int closeBracket = 0;
        for(int i = n-1;i>=0;i--){
            if(locked[i] == '0'){
                closeBracket++;
                anyBracket--;
            }
            else if (s[i] == '('){
                closeBracket--;
                openBracket--;
            }else if(s[i] == ')'){
                closeBracket++;
            }
            if(closeBracket < 0){
                return false;
            }
            if(openBracket == 0 && anyBracket == 0) break;
        }
        if(openBracket > 0) return false;
        return true;
    }
};