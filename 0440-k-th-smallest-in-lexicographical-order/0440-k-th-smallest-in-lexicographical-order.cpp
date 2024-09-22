class Solution {
public:
    int findStep(int n, long long curr, long long next){
        int step = 0;
        while(curr <= n){
            step += min((long long)n+1,next) - curr;
            curr = curr * 10;
            next = next * 10;
        }
        return step;
    }
    int findKthNumber(int n, int k) {
        int i = 1; 
        while(i <= n){
            int step = findStep(n,i,i+1);
            if(step >= k){
                i = i*10;
                k--;
            }
            else{
                k -= step;
                i++;
            }
            if(k == 1) return i;
        }
        return 1;
    }
};