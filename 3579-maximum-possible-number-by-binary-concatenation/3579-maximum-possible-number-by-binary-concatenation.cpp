class Solution {
public:

    static bool compare(int a,int b){
        string s1 = "";
        string s2 = "";
        while(a){
            int bit = 1&a;
            a = a>>1;
            s1 = to_string(bit) + s1;
        }
        while(b){
            int bit = 1&b;
            b = b>>1;
            s2 = to_string(bit) + s2;
        }
        return s1+s2 < s2+s1;
    }
    int maxGoodNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end(),compare);
        int res = 0;
        int count = 0;
        for(int i = 0;i < 3;i++){
            int n = nums[i];
            cout<<n<<endl;
            while(n){
                int bit = n&1;
                n = n>>1;
                res = res|(bit<<count);
                count+=1;
            }
        }
        return res;
    }
};