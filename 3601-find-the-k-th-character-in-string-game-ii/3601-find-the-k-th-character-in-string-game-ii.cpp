class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        string s = "";
        int sum = 0;
        char res = 'a';
        while(k > 0){
            int l = 0;
            while((1LL<<l) < k) l++;
            if(k % (1LL<<l) == 0){
                sum += accumulate(operations.begin(),operations.begin()+l,0);
                res = res + (sum%26);
                break;
            }
            k = k % (1LL<<(l-1));
            sum += l == 0 ? operations[0] : operations[l-1];
        }
        return res;
    }
};