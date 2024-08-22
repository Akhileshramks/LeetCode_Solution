class Solution {
public:
    int findComplement(int num) {
        int temp = num;
        int xor1 = 0;
        while(temp){
            xor1 = xor1<<1 | 1;
            temp = temp>>1;
        }
        return num^xor1;
    }
};