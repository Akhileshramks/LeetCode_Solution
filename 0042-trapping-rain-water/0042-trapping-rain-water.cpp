class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int low = 0;
        int high = n-1;
        int sum = 0;
        int maxi1 = 0;
        int maxi2 = 0;
        while(low<=high){
            if(height[low]<=height[high]){
                if(height[low]>maxi1){
                    maxi1 = height[low];
                }
                else{
                    sum += maxi1-height[low];
                }
                low++;
            }
            else{
                if(height[high]>maxi2){
                    maxi2 = height[high];
                }
                else{
                    sum += maxi2-height[high];
                }
                high--;
            }
        }
        return sum;
    }
};