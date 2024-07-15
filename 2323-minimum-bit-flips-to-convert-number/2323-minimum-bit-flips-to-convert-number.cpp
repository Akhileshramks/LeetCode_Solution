class Solution {
public:
    int minBitFlips(int start, int goal) {
        int m = start^goal;
        int count = 0;
        while(m){
            if(m&1) count++;
            m = m>>1;
        }
        return count;
    }
};