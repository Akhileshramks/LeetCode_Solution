class Solution {
public:
    static bool comparator(const string &a,const string &b){
        return a+b > b+a;
    }
    string largestNumber(vector<int>& nums) {
        int sum = 0;
        vector<string> res;
        int count = 0;
        for(int i : nums)
            if(i == 0) count++;
        if(count == nums.size()) return "0";
        for(int i : nums){
            res.push_back(to_string(i));
        }
        string s = "";
        sort(res.begin(),res.end(),comparator);
        for(string t : res) s += t;
        return s;
    }
};