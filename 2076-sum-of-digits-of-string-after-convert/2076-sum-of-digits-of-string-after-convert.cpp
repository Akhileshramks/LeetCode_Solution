class Solution {
public:
    int getLucky(string s, int k) {
        string numericString = "";
        for (char ch : s) {
            numericString += to_string(ch - 'a' + 1);
        }

        while (k-- > 0) {
            int digitSum = 0;
            for (char digit : numericString) {
                digitSum += digit - '0';
            }
            numericString = to_string(digitSum);
        }
        return stoi(numericString);
    }
};