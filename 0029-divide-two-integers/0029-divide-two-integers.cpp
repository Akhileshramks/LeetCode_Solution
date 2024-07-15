class Solution {
public:
    int divide(int dividen, int diviso) {
        if(dividen == diviso) return 1;
        long ans  = 0;
        
        bool sign = (dividen < 0) == (diviso < 0);
        unsigned int dividend = abs(dividen);
        unsigned int divisor = abs(diviso);
        while(dividend>=divisor){
            int cnt = 0;
            while(dividend>(divisor<<(cnt+1))){
                cnt++;
            }
            ans += (1<<cnt);
            dividend -= (divisor<<cnt);
        }
        if(ans>INT_MAX && sign) return INT_MAX;
        if(ans<INT_MIN && !sign) return INT_MAX;
        return sign ? ans : -ans;
    }
};