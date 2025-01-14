class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        unordered_map<int,int> mpp;
        int n = A.size();
        vector<int> res;
        int count = 0;
        for(int i = 0; i < n; i++){
            mpp[A[i]]++;
            mpp[B[i]]++;
            if(mpp[A[i]] == 2) count++;
            if(mpp[B[i]] == 2 && B[i] != A[i]) count++;
            res.push_back(count);
        }
        return res;
    }
};