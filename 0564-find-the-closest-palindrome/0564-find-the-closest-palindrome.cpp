class Solution {
public:
    long make_palindrome(long m,bool even){
        long res = m;
        if(even == 0){
            m = m/10;
        }
        
        while(m){
            res = res*10 + m%10;
            m = m/10;
        }
        return res;
    }
    string nearestPalindromic(string s) {
        int n = s.size();
        int mid = n%2 == 0 ? n/2-1 : n/2;
        long left = stol(s.substr(0,mid+1));
        long original = stol(s);
        vector<long> ans;
        ans.push_back(make_palindrome(left,n%2 == 0));
        ans.push_back(make_palindrome(left+1,n%2 == 0));
        ans.push_back(make_palindrome(left-1,n%2 == 0));
        ans.push_back(pow(10,n-1)-1);
        ans.push_back(pow(10,n)+1);

        long diff = INT_MAX;
        long pal = original;
        for(const auto& i : ans){
            if(original == i) continue;
            cout<<i<<" ";
            if(diff>abs(original-i)){
                pal = i;
                diff = abs(original - i);
            }
            else if(diff == abs(original-i)){
                pal = min(i,pal);
            }
        }
        return to_string(pal);

    }
};