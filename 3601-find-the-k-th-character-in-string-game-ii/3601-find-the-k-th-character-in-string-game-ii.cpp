class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int sum = 0;
        char res = 'a';
        while(k > 0){
            int ind = 0;
            long long largestExp = 1;
            while(largestExp < k){
                largestExp *= 2;
                ind++;
            }
            if(k % largestExp == 0){
                sum += accumulate(operations.begin(),operations.begin()+ind,0);
                res = res + (sum%26);
                break;
            }
            k = k % (largestExp/2);
            sum += ind == 0 ? operations[0] : operations[ind-1];
        }
        return res;
    }
};