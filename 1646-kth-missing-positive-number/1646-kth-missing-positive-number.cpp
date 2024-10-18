class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n = 0;
        int ind = 0;
        while(k > 0 && ind < arr.size()){
            n++;
            if(arr[ind] != n) k--;
            else ind++;
        }
        return n + k;
    }
};