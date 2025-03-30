class Solution {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char,int> lastOccurence;
        int i = 0;
        for(char c : s) lastOccurence[c] = i++;
        int last = 0;
        int end = -1;
        vector<int> ans;
        int n = s.size();
        for(int i = 0;i < n;i++){
            last = max(lastOccurence[s[i]],last);
            if(i == last){
                ans.push_back(i - end);
                end = i;
            }
        }
        return ans;
    }
};