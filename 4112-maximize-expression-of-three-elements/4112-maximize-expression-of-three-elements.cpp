class Solution {
public:
    int maximizeExpressionOfThree(vector<int>& nums) {
        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        int secondMaxElement = INT_MIN;
        int n = nums.size();
        for(int i = 0;i < n;i++){
            if(nums[i] < minElement) minElement = nums[i];
            if(nums[i] > maxElement){
                secondMaxElement = max(secondMaxElement, maxElement);
                maxElement = nums[i];
            }else if(nums[i] > secondMaxElement){
                secondMaxElement = max(nums[i], secondMaxElement);
            }
        }
        return maxElement + secondMaxElement - minElement;
    }
};