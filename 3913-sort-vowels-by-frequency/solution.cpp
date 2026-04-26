class Solution {
public:
    string sortVowels(string s) {
        unordered_map<char,int> freqCount, firstIndex;
        for(int i = 0;i < s.size();i++){
            char c = s[i];
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                freqCount[c] += 1;
                if(firstIndex.find(c) == firstIndex.end()) firstIndex[c] = i;
            }
        }
        vector<char> vowel;
        for(auto i : firstIndex) vowel.push_back(i.first);
        sort(vowel.begin(), vowel.end() ,[&] (char a, char b){
            if(freqCount[a] == freqCount[b]) return firstIndex[a] < firstIndex[b];
            return freqCount[a] > freqCount[b];
        });
        int curr = 0;
        string result = s;
        for(int i = 0; i < result.size(); i++){
            char c = result[i];
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
                result[i] = vowel[curr];
                freqCount[vowel[curr]]--;
                if(freqCount[vowel[curr]] == 0) curr++;
            }
        }
        return result;
    }
};