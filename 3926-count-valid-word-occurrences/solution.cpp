class Solution {
public:
    bool isLower(char c){
        return 'a' <= c && c <= 'z';
    }
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries) {
        unordered_map<string,int> mpp;
        string s = "";
        for(auto i : chunks) s += i;
        int n = s.size();
        string word = "";
        for(int i = 0;i < n;i++){
            if(isLower(s[i]) || (s[i] == '-' && i - 1 >= 0 && isLower(s[i - 1]) && i + 1 < n && isLower(s[i+1]))) word += s[i];
            else{
                mpp[word]++;
                word = "";
            }
        }
        mpp[word]++;
        vector<int> res;
        for(auto m : queries) res.push_back(mpp[m]);
        return res;
    }
};