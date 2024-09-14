class Solution {
public:
    static bool compare(const vector<int>& a,const vector<int> &b){
        if(a[0] == b[0]) return a[1]>b[1];
        return a[0]<b[0];
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),compare);
        int n = envelopes.size();
        vector<int> res;
        for(int i =0;i<n;i++){
            if(res.size() == 0 || res.back()<envelopes[i][1]){
                res.push_back(envelopes[i][1]);
            }
            else{
                int ind = lower_bound(res.begin(),res.end(),envelopes[i][1])-res.begin();
                res[ind] = envelopes[i][1];
            }
        }
        return res.size();
    }
};