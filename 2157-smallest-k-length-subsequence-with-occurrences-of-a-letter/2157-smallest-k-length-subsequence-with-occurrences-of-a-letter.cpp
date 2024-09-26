class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.size();
        int count = 0;
        for(int i = 0 ; i < n; i++ ){
            if(s[i] == letter) count++;
        }
        int rest = count;
        int need = repetition;
        string res = "";
        for(int i = 0; i < n; i++ ){
            while( !res.empty() && res.back() > s[i] && res.size() + n - i > k){
                if(res.back() == letter && rest - need <= 0) break;
                if(res.back() == letter) need++;
                res.pop_back();
            }
            if(res.size() < k){
                if(s[i] == letter){
                    res.push_back(s[i]);
                    need--;
                }
                else if(res.size() + need < k){
                    res.push_back(s[i]);
                }
            }
            if(s[i] == letter) rest--;
        }
        
        return res;
    }
};