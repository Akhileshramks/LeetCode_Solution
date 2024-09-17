class KthLargest {
public:
    int k_val;
    priority_queue<int,vector<int>,greater<int>> pq;
    KthLargest(int k, vector<int>& nums) {
        for(int i : nums){
            pq.push(i);
            if(pq.size()>k) pq.pop();
        }
        k_val = k;
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size()>k_val){
            pq.pop();
        }
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

 /*

2 5 8

 */