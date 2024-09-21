class Solution {
public:
    string shortestPalindrome(string s) {
        string rev = s;
        reverse(rev.begin(),rev.end());
        string new_string = s + "#" + rev;
        int n = new_string.size();
        vector<int> lps(n,0);
        int length = 0;
        for(int i = 1;i < n;i++){
            while(length > 0 && new_string[i] != new_string[length]){
                length = lps[length-1];
            } 
            if(new_string[i] == new_string[length]) length++;
            lps[i] = length;
        }
        int m = lps[n-1];
        return rev.substr(0,s.size() - m) + s;
    }
};


/*

 a a c e c a a a # a a a c e c a a
 0 1 0 0 0 1 2 2 0 1 2 2 3 4 5 6 7           
   l                              
*/