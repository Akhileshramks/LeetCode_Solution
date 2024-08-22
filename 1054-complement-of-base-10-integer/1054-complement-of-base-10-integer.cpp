class Solution {
public:
    int bitwiseComplement(int num) {
        int temp = num;
        int xor1 = 0;
        if(num == 0){
            return 1;
        }
        while(temp){
            xor1 = xor1<<1 | 1;
            temp = temp>>1;
        }
        return num^xor1;
    }
};