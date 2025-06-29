class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int ans = 0;
        unordered_map<char,int> lastSeen;
        
        for(right = 0; right < n; right++){
            if(lastSeen.find(s[right]) != lastSeen.end() && lastSeen[s[right]] >= left){
                left = lastSeen[s[right]] + 1;
            }
            ans = max(ans, right - left + 1);
            lastSeen[s[right]] = right;
        }
        return ans;
    }
};