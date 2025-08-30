class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = needle.size();
        vector<int> lps(n, 0);
        int length = 0;
        int i = 1;
        while(i < n){
            if(needle[i] == needle[length]){
                length++;
                lps[i] = length;
                i++;
            }else{
                if(length != 0){
                    length = lps[length-1];
                }else{
                    lps[i] = 0;
                    i++;
                }
            }
        }

        int j = 0;
        i = 0;
        while(i < haystack.size()){
            if(haystack[i] == needle[j]){
                i++;
                j++;
            }else{
                if(j > 0) j = lps[j-1];
                else i++;
            }
            if(j == needle.size()) return i - needle.size();
        }
        return -1;
    }
};