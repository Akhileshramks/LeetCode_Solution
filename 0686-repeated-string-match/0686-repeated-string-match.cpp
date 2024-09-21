class Solution {
public:
    bool kmp(string haystack,string needle){
        int p = needle.size();
        int n = haystack.size();
        vector<int> lps(p,0);

        int length = 0;
        for(int i = 1;i < p; i++ ){
            while(length > 0 && needle[i] != needle[length]) length = lps[length-1];
            if(needle[i] == needle[length]) length++;
            lps[i] = length;
        }
        int low = 0;
        for(int i = 0;i < n; i++ ){
            while(low > 0 && needle[low] != haystack[i]) low = lps[low-1];
            if(needle[low] == haystack[i]) low++;
            if(low == p) return true;
        }
        return false;
    }
    int repeatedStringMatch(string a, string b) {
        int n_a = a.size();
        int n_b = b.size();
        int n = n_b / n_a;
        int cnt = n;

        string new_a = "";
        while(cnt--) new_a += a;

        if(kmp(new_a,b)) return n;
        new_a += a;
        if(kmp(new_a,b)) return n+1;
        new_a += a;
        if(kmp(new_a,b)) return n+2;
        return -1;
    }
};