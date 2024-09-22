class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string s = countAndSay(n-1);
        int m = s.size();
        int k = 1;
        int start = s[0]-'0';
        string res = "";
        for(int i = 1;i<m;i++){
            if(s[i]-'0' != start){
                res += (to_string(k) + to_string(start));
                start = s[i]-'0';
                k = 1;
            }
            else k++;
        }
        res += to_string(k) + to_string(start);
        cout<< res<<" ";
        return res;
    }
};