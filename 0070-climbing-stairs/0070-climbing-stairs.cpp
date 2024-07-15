class Solution {
public:
    int climbStairs(int n) {
        if(n<=1) return n;
        int prev = 1;
        int curr = 2;
        int temp;
        for(int i=3;i<=n;i++){
            temp = curr+prev;
            prev = curr;
            curr = temp;
        }
        return  curr;
    }
};