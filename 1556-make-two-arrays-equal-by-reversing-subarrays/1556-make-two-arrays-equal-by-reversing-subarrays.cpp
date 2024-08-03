class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        // Frequency count for arr
        unordered_map<int, int> arrFreq;
        for (int num : arr) {
            arrFreq[num]++;
        }

        for (int num : target) {
            // If num does not appear in target, then arrays are not equal
            if (arrFreq.find(num) == arrFreq.end()) return false;

            // Decrement the frequency count for num and
            // remove key if the count goes to 0
            arrFreq[num]--;
            if (arrFreq[num] == 0) {
                arrFreq.erase(num);
            }
        }
        return arrFreq.size() == 0;
    }
};