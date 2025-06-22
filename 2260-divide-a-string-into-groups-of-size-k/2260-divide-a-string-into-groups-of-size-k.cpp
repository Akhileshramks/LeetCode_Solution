class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        int n = s.size();

        int noOfGroups = n / k;
        int need = n % k;
        int i = 0;
        vector<string> ans;
        int count = 0;
        while(count < noOfGroups){
            ans.push_back(s.substr(i,k));
            i += k;
            count++;
        }

        if(i < n) ans.push_back(s.substr(i) + string(k - need, fill));
        return ans;
    }
};

/*

abcdefghi
012345678

*/