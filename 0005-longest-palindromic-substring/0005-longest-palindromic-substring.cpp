class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int maxi = 1;
        int start = 0;
        for(int i = 0;i<n;i++){
            int low = i;
            int high = i;
            while(low >= 0 && high < n && s[low] == s[high]){
                    low--;
                    high++;
            }
            if(maxi < (high-low-1)){
                maxi = high-low-1;
                start = low+1;
            }
        }
        for(int i = 0;i<n;i++){
            int low = i-1;
            int high = i;
            while(low >= 0 && high < n && s[low] == s[high]){
                    low--;
                    high++;
            }
            if(maxi < (high-low-1)){
                maxi = high-low-1;
                start = low+1;
            }
        }
        return s.substr(start,maxi);
    }
};