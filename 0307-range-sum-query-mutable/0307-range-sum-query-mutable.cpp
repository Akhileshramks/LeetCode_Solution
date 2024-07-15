class NumArray {
public:
    int n;
    vector<int> seg;
    NumArray(vector<int>& nums) {
        n = nums.size();
        seg.resize(4*n);
        build(0,0,n-1,nums);
    }
    void build(int ind,int low,int high,vector<int>& nums){
        if(low == high) {
            seg[ind] = nums[low];
            return;
        }
        int mid = (low+high)/2;
        build(2*ind+1,low,mid,nums);
        build(2*ind+2,mid+1,high,nums);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
        return;
    }
    void update_val(int ind,int low,int high,int val,int i){
        if(low == high){
            seg[ind] = val;
            return;
        } 
        int mid = (low+high)/2;
        if(i<=mid) update_val(2*ind+1,low,mid,val,i);
        else update_val(2*ind+2,mid+1,high,val,i);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
        return;
    }
    int sum_range(int ind,int low,int high,int l,int r){
        if(r<low || l>high) return 0;
        else if(l<=low && high<=r){
            return seg[ind];
        }
        int mid = (low+high)/2;
        int left = sum_range(2*ind+1,low,mid,l,r);
        int right = sum_range(2*ind+2,mid+1,high,l,r);
        int sum = left+right;
        return sum;
    }
    void update(int index, int val) {
        update_val(0,0,n-1,val,index);
    }
    
    int sumRange(int left, int right) {
        return sum_range(0,0,n-1,left,right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */