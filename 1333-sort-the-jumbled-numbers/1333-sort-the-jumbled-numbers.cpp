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
            if(l1[i]<=l2[j]){
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
    bool static cmp(const pair<int,int> &a, const pair<int,int> &b) {
        if (a.first == b.first)
            return false;
        return a.first < b.first;
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
        vector<int> m;
        vector<pair<int,int>> mp;
        for(int i =0;i<n;i++){
            int mapped = compare(nums[i],mapping);
            mp.push_back({mapped,nums[i]});
        }
        //mergesort(0,n-1,m,mapping);
        sort(mp.begin(),mp.end(),cmp);
        for(int i =0;i<n;i++){
            nums[i] = mp[i].second;
        }
        return nums;
    }
};