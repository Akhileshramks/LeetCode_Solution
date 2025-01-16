class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int result = 0;
        if(n1 % 2 == 0 && n2 % 2 == 0) return result;
        if(n1 % 2 == 1 && n2 %2 == 1){
            for(int i = 0;i < n1;i++) result ^= nums1[i]; 
            for(int i = 0;i < n2;i++) result ^= nums2[i]; 
            return result;
        }
        if(n1 % 2 == 0){
            for(int i = 0;i < n1;i++) result ^= nums1[i]; 
        }
        if(n2 % 2 == 0){
            for(int i = 0;i < n2;i++) result ^= nums2[i]; 
        }
        return result;
    }
};