class Solution {
public:
    int sumOfDigit(int n){
        int sum = 0;
        while(n > 0){
            sum += n%10;
            n = n/10;
        }
        return sum;
    }
    int maximumSum(vector<int>& nums) {
        unordered_map<int,int> digitSum;
        int maxi = -1;

        for(int i : nums){
            int sum = sumOfDigit(i);
            if(digitSum.find(sum) != digitSum.end()){
                maxi = max(maxi,digitSum[sum] + i);
                digitSum[sum] = max(digitSum[sum],i);
            }
            else{
                digitSum[sum] = i;
            }
        }
        return maxi;
    }
};