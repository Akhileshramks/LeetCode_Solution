class Solution {
public:
    int strStr(string haystack, string needle) {
        int p = needle.size();
        int length = 0;
        vector<int> lps(p,0);
        for(int i =1;i<p;i++){
            while(length > 0 && needle[i] != needle[length]) length = lps[length-1];
            if(needle[i] == needle[length]) length++;
            lps[i] = length;
        }
        int n = haystack.size();
        int low = 0;
        for(int i = 0;i<n;i++){
            while(haystack[i] != needle[low] && low>0) low = lps[low-1];
            if(haystack[i] == needle[low]) low++;
            if(low == p) return i-p+1;
        }
        return -1;
    }
};