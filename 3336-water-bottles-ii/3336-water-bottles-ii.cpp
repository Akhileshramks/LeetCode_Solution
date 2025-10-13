class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int full_bottles = numBottles;
        int result = 0;
        int remainder = 0;
        int quotient = 0;
        while((full_bottles + remainder) >= numExchange){
            result += full_bottles;
            quotient = 1;
            remainder = remainder + full_bottles - numExchange;
            full_bottles = quotient;
            numExchange++;
        }

        return result + full_bottles;
    }
};