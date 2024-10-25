class Solution {
public:
    double myPow(double x, int n) {
        if(n < 0){
            n = abs(n);
            x = 1/x;
        }
        double pow = 1;
        while(n){
            if(n & 1){
                pow = pow * x;
            }
            x *= x;
            n /= 2;
        }
        return pow;
    }
};