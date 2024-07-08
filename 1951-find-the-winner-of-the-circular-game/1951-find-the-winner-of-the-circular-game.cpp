class Solution {
public:
    int findTheWinner(int n, int k) {
        int current = 0;
        for(int i=1;i<n+1;i++) current = (current+k)%i;
        return current+1;
    }
};