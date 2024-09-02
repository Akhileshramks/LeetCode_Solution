#define ll long long
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        long sum = accumulate(chalk.begin(),chalk.end(),0ll);
        k = k % sum;
        int ind =0;
        while(k>=0){
            k-=chalk[ind];
            ind++;
        }
        return ind-1;
    }
};