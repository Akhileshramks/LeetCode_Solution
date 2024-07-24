class Solution {
public:
    int compare(int n, vector<int>& mapping) {
        int ans = 0;
        int factor = 1;
        if(n==0) return mapping[0];
        while (n > 0) {
            int digit = n % 10;
            ans += mapping[digit] * factor;
            factor *= 10;
            n /= 10;
        }
        return ans;
    }
    void merge(int l,int mid,int h,vector<int>& nums,vector<int>& mapping){
        int n1 = mid-l+1;
        int n2 = h-mid;
        vector<int> l1(n1);
        vector<int> l2(n2);
        int i = 0;
        int j= 0;
        while(i<n1){
            l1[i] = nums[l+i];
            i++;
        }
        while(j<n2){
            l2[j] = nums[mid+j+1];
            j++;
        }
        int k = l;
        i=0,j=0;
        while(i<n1 && j<n2){
            if(compare(l1[i],mapping)<=compare(l2[j],mapping)){
                nums[k] = l1[i];
                i++;
                k++;
            }
            else{
                nums[k] = l2[j];
                j++;
                k++;
            }
        }
        while(i<n1){
            nums[k] = l1[i];
            i++;
            k++;
        }
        while(j<n2){
            nums[k] = l2[j];
            j++;
            k++;
        }
    }
    void mergesort(int l,int h,vector<int>& nums,vector<int>& mapping){
        if(l<h){
            int mid = l+(h-l)/2;
            mergesort(l,mid,nums,mapping);
            mergesort(mid+1,h,nums,mapping);
            merge(l,mid,h,nums,mapping);
        }
    }
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        int n = nums.size();
        for(int i =0;i<n;i++){
            cout<<compare(nums[i],mapping)<<" ";
        }
        
        mergesort(0,n-1,nums,mapping);
        return nums;
    }
};