class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int sum = 0;
        char res = 'a';
        while(k != 1){
            int ind = 0;
            long long largestExp = 1;
            while(largestExp < k){
                largestExp *= 2;
                ind++;
            }
            k = k - (largestExp/2);
            sum += operations[ind-1];
        }
        res = res + (sum%26);
        return res;
    }
};