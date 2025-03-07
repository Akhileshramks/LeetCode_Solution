class Solution {
public:
    bool isPrime(int m){
        if(m == 1) return false;
        for(int i = 2;i*i <= m;i++){
            if(m % i == 0) return false;
        }
        return true;
    }
    vector<int> closestPrimes(int left, int right) {
        int num1 = -1;
        int res1 = -1,res2 = -1;
        for(int i = left;i <= right;i++){
            if(isPrime(i)){
                if(num1 != -1 && ((res1 == -1 && res2 == -1) || (res2 - res1 > i - num1))){
                    res1 = num1;
                    res2 = i;
                }
                num1 = i; 
            }
        }
        return {res1,res2};
    }
};