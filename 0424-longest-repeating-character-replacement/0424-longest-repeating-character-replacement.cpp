class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0,right = 0,n = s.size();
        unordered_map<char,int> freqCount;
        int ans = 0,maxFreq = 0;
        for(right = 0;right <n;right++){
            freqCount[s[right]]++;
            maxFreq = max(maxFreq,freqCount[s[right]]);
            while(right - left + 1 - maxFreq > k && left <= right){
                freqCount[s[left]]--;
                left++;
            }

            ans = max(ans, right- left + 1);
        }
        return ans;
    }

};