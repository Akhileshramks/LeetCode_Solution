class Solution {
public:
    string compressedString(string word) {
        string comp = "";
        int pos = 0;
        while (pos < word.length()) {
            int consecutiveCount = 0;
            char currentChar = word[pos];
            while (pos < word.length() && consecutiveCount < 9 &&
                   word[pos] == currentChar) {
                consecutiveCount++;
                pos++;
            }
            comp += to_string(consecutiveCount) + currentChar;
        }
        return comp;
    }
};