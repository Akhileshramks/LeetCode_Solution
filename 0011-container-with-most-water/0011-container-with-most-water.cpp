class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int low = 0;
        int high = n-1;
        long long maxi = 0;
        int w;
        while(low<=high){
            w = ((high-low)*min(height[low],height[high]));
            if(maxi<w) maxi=w;
            if(height[low]>=height[high]){
                high--;
            }
            else{
                low++;
            }
           
        }
        return maxi;
    }
};