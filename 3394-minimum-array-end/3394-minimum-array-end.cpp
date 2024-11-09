class Solution {
public:
    long long minEnd(int n, int x) {
        n--;
        long long res = x;
        int bit = 0;
        while(n > 0){
            if(!(1LL<<bit & x)){
                res |= (n & 1) * (1LL<<bit);
                n>>=1;
            }
            bit++;
        }
        return res;
    }
};
