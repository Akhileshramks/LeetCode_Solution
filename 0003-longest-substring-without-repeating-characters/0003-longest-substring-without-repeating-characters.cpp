class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int ans = 0;
        unordered_map<char,int> freqCount;
        
        for(right = 0; right < n; right++){
            freqCount[s[right]]++;
            while(freqCount[s[right]] > 1){
                freqCount[s[left]]--;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};