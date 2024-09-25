class Solution {
public:
    int numSplits(string s) {
        int n = s.size();
        unordered_map<int,int> start,end;
        for(int i =0;i<26;i++){
            start[i] = -1;
            end[i] = -1;
        }
        vector<int> res;
        for(int i =0;i<n;i++){
            if(start[s[i] - 'a'] == -1){
                start[s[i] - 'a'] = i;
            }
            end[s[i] - 'a'] = i;
        }
        for(auto i : start){
            if(i.second != -1) res.push_back(i.second);
        }
        for(auto i : end){
            if(i.second != -1) res.push_back(i.second);
        }
        sort(res.begin(),res.end());
        int mid = res.size()/2;
        return res[mid] - res[mid-1];
    }
    int numSplits1(string s) {
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