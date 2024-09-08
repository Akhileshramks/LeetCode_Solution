class Solution {
public:
    void merge(vector<int>& nums,int low,int mid,int high){
        int n1 = mid-low+1;
        int n2 = high-mid;
        int i = low, j= mid+1,k = low;
        int count = 0;
        vector<int> ans;
        while(i<=mid && j<=high){
            if(nums[i]<nums[j]){
                ans.push_back(nums[i]);
                i++;
            }
            else{
                count += mid-i+1;
                ans.push_back(nums[j]);
                j++;
            }
        }
        while(i<=mid){
            ans.push_back(nums[i]);
            i++;
        }
        while(j<=high){
            ans.push_back(nums[j]);
            j++;
        }
        for(int i =0;i<n1+n2;i++){
            nums[k] = ans[i];
            k++;
        }
    }
    int countInversions(vector<int>& nums,int low,int mid,int high){
        int i = low, j= mid+1;
        int count = 0;
        while(i<=mid && j<=high){
            if(nums[i]> 2*(long)nums[j]){
                j++;
                count += mid-i+1;
            }
            else i++;
        }
        return count;
    }
    int mergesort(vector<int>& nums,int low,int high){
        int count = 0;
        if(low<high){
            int mid = low + (high-low)/2;
            count += mergesort(nums,low,mid);
            count += mergesort(nums,mid+1,high);
            count += countInversions(nums,low,mid,high);
            merge(nums,low,mid,high);
        }
        return count;
    }
    int reversePairs(vector<int>& nums) {
        return mergesort(nums,0,nums.size()-1);
    }
};