class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int op = 0;
        for(int i = 0;i < n;i++){
            if(nums[i] == 1) continue;
            else if(nums[i] == 0 && i < n - 2){
                nums[i+1] ^= 1;
                nums[i+2] ^= 1;
                op++;
            }
            else{
                return -1;
            }
        }
        return op;
    }
};
/*

1 1 1 
0 0 0

1 1 1 1
0 0 0 1
1 0 0 0
0 1 1 0

1 1 1 1 1
0 0 0 1 1
1 0 0 0 1
1 1 0 0 0
0 1 1 0 0
0 0 1 0 0
0 1 1 0 1
1 0 1 1 0
0 0 1 0 0
1 0 1 1 0
*/