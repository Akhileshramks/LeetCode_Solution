class Solution {
public:
    int maxDelete(int x){
        int powerof3 = 1;
        while(powerof3 * 3 <= x) powerof3 *= 3;
        return powerof3;
    }
    bool checkPowersOfThree(int n) {
        int prev = -1,current = 0;
        while(n > 0){
            current = maxDelete(n);
            if(current == prev) return false;
            n = n - current;
            if(n == 0) return true;
            prev = current;
        }
        return false;
    }
};