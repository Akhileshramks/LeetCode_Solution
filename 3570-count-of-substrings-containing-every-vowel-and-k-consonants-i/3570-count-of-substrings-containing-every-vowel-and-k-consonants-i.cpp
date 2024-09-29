class Solution {
public:
    bool isVowel(char i){
        return i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u';
    }
    int countSubstrings(string s,int k){
        int VowelCount = 0;
        int res = 0;
        int i = 0;
        int low = 0;
        int n = s.length();
        int consonant = 0;
        unordered_map<char,int> mpp;
        while(i < n){
            if(isVowel(s[i])){
                if(mpp.find(s[i]) == mpp.end()){
                    VowelCount += 1;
                }
                mpp[s[i]] = i;
            }
            else{
                consonant += 1;
            }
            while(VowelCount == 5 && consonant>=k){
                res += n-i;
                if(isVowel(s[low])){
                    if(mpp[s[low]] == low){
                        VowelCount--;
                        mpp.erase(s[low]);
                    }
                }
                else{
                    consonant--;
                }
                low++;
            }
            i++;
        }
        return res;
    }
    int countOfSubstrings(string word, int k) {
        int n1 = countSubstrings(word,k);
        int n2 = countSubstrings(word,k+1);
        return n1-n2;
    }
};

/*
ieaouqqieaouqq

>=k
_______k____k+1
*/