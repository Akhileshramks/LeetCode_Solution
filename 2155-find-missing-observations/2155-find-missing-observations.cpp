class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int total = n+m;
        int total_sum = mean * total;
        int sum_m = accumulate(rolls.begin(),rolls.end(),0);
        int sum_n = total_sum - sum_m;
        double avg_n = sum_n / n;
        int avg_n1 = sum_n / n;
        
        if (sum_n < n || sum_n > 6 * n) {
            return {};
        }
        vector<int> res(n,sum_n/n);
        int remainder = sum_n % n;
        for(int i =0 ;i<remainder;i++){
            res[i]++;
        }
        return res;
    }
};