class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<string> result;
        unordered_map<int,int> mppWord2;
        for(string s : words2){
                unordered_map<int,int> word2Char;
                for(char c : s) word2Char[c-'a']++;
                for(int i = 0;i < 26;i++) mppWord2[i] = max(mppWord2[i],word2Char[i]);
        }

        for(string s : words1){
            unordered_map<int,int> mppWord1;
            bool flag = true;
            for(char c : s){
                mppWord1[c-'a']++;
            }
            for(int i=0; i< 26;i++){
                if(mppWord1[i] < mppWord2[i]){
                    flag = false;
                    break;
                }
            }
            if(flag) result.push_back(s);
        }
        return result;
    }
};