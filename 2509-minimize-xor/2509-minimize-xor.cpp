class Solution {
public:
    int noOfSetBits(int num){
        int count = 0;
        while(num){
            if(num & 1) count++;
            num >>= 1;
        }
        return count;
    }
    int minimizeXor(int num1, int num2) {
        int n1 = noOfSetBits(num1);
        int n2 = noOfSetBits(num2);
        if(n1 == n2) return num1;
        else if(n1 > n2){
            n1 = n1 - n2;
            for(int i = 0;i <= 31 && n1 > 0;i++){
                if((num1 & 1<<i) != 0){
                    num1 ^= (1<<i);
                    n1--;
                }
            }
        }else{
            n1 = n2 - n1;
            for(int i = 0;i <= 31 && n1 > 0;i++){
                if((num1 & 1<<i) == 0){
                    num1 ^= (1<<i);
                    n1--;
                }
            }
        }
        return num1;

    }
};