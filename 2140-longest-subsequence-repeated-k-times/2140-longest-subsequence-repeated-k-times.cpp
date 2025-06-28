class Solution {
public:
    bool isValid(string &s, string &check, int k){
        int n = s.size();
        int m = check.size();
        int pos = 0;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(check[pos] == s[i]) pos++;
            if(pos  == m){
                count++;
                pos = 0;
            }
        }
        if(count >= k) return true;
        return false;
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> freqCount(26,0);
        for(char c : s) freqCount[c-'a']++;

        vector<char> kFreq;
        for(int i = 25;i >= 0;i--){
            if(freqCount[i] >= k){
                kFreq.push_back('a' + i);
            }
        }

        queue<string> q;
        for(char c : kFreq) q.push(string(1, c));

        string ans = "";
        while(!q.empty()){
            string front = q.front();
            q.pop();
            if(ans.size() < front.size()){
                ans = front;
            }
            for(char c : kFreq){
                string next = front + c;
                if(isValid(s, next, k)){
                    q.push(next);
                }
            }
        }
        return ans;
    }
};