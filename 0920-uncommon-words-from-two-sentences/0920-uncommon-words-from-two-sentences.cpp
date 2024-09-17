class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string,int> wordCount;
        stringstream ss1(s1);
        string i;
        while(ss1 >> i) wordCount[i]++;
        stringstream ss2(s2);
        while(ss2 >> i) wordCount[i]++;
        vector<string> res;
        for(auto i : wordCount){
            if(i.second == 1) res.push_back(i.first);
        }
        return res;

    }
};