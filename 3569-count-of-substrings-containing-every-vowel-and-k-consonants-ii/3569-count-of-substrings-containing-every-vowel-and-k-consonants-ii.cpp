class Solution {
public:
    long long countOfSubstrings(string word, int k){
        return countOfAtleastSubstrings(word,k) - countOfAtleastSubstrings(word,k+1);
    }
    long long countOfAtleastSubstrings(string word, int k) {
        unordered_map<char, int> vowel = { {'a', 0}, {'e', 0}, {'i', 0}, {'o', 0}, {'u', 0} };
        int consonants = 0;
        int n = word.length();
        int low = 0,high = 0;
        long long res = 0;
        while(high < n){
            if(word[high] == 'a' || word[high] == 'e' || word[high] == 'i' || word[high] == 'o' || word[high] == 'u') vowel[word[high]]++;
            else consonants++;
            while(low < n && vowel['a'] > 0 && vowel['e'] > 0 && vowel['i'] > 0 && vowel['o'] > 0 && vowel['u'] > 0 && consonants >= k){
                res += n - high;
                if(word[low] == 'a' || word[low] == 'e' || word[low] == 'i' || word[low] == 'o' || word[low] == 'u') vowel[word[low]]--;
                else consonants--;
                low++;
            }
            high++;
        }
        return res;
    }
};