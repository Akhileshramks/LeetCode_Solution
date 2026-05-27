class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> lowerInd(26, INT_MAX), upperInd(26, INT_MIN);
        int n = word.size();
        int count = 0;
        for(int i = 0;i < n;i++){
            if(word[i] >= 'a' && word[i] <= 'z') lowerInd[word[i] - 'a'] = i;
            else if(word[i] >= 'A' && word[i] <= 'Z' && upperInd[word[i] - 'A'] == INT_MIN) upperInd[word[i] - 'A'] = i;
        }
        for(int i = 0;i < 26;i++){
            if(lowerInd[i] < upperInd[i]) count++;
        }
        return count;
    }
};