class Solution {
public:
    int numberOfSubstrings(string s) {
        int a = 0,b = 0,c = 0;
        int low = 0,high = 0,res = 0;
        int n = s.size();
        while(high < n){
            if(s[high] == 'a') a++;
            else if(s[high] == 'b') b++;
            else if(s[high] == 'c') c++;
            while(a > 0 && b > 0 && c > 0 && low < n){
                res += (n - high);
                if(s[low] == 'a') a--;
                else if(s[low] == 'b') b--;
                else if(s[low] == 'c') c--;
                low++;
            } 
            high++;
        }
        return res;
    }
};