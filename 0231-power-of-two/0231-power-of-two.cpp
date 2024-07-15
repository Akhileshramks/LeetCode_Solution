class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n>0) return (n &(n-1)) == 0 ? true : false;
        else return false;
    }
};