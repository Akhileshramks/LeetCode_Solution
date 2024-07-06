class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char,int> d;
        int left = 0;
        int right = 0;
        int n = s.size();
        int maxf = 0;
        int maxi = 0;
        while(right<n){
            d[s[right]]++;
            maxf = max(maxf, d[s[right]]);
            if(((right-left+1)-maxf)>k){
                d[s[left]]--;
                left++;
            }
            else{
                maxi = max(maxi,right-left+1);
            }
            right++;
        }
        return maxi;

    }
};