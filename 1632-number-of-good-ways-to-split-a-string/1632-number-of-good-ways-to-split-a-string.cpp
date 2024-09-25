class Solution {
public:
    int numSplits(string s) {
        int n = s.size();
        unordered_set<int> leftSet,rightSet;
        vector<int> left(n,0),right(n,0);
        for(int i =0;i<n;i++){
            leftSet.insert(s[i]);
            rightSet.insert(s[n-1-i]);
            right[n-1-i] = rightSet.size();
            left[i] = leftSet.size();
        }
        int res = 0;
        for(int i = 1;i < n; i++){
            if(left[i-1] == right[i]) res++;
        }
        return res;
    }
};