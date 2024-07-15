class Solution {
public:
    int countPrimes(int n) {
        vector<int> prime(n,1);
        int count = 0;

        for(int i = 2;i*i<n;i++){
            if(prime[i] == 1){
                for(int j=i*i;j<n;j+=i){
                    prime[j] = 0;
                }
            }
        }
        for(int i=2;i<n;i++){
            if(prime[i]) count++;
        }
        return count;
    }
};