class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char,int> mpp,s1Map;
        for(auto & i : s1){
            mpp[i]++;
            s1Map[i]++;
        }
        int low = 0;
        int n = s2.size();
        int high = 0;
        int m = s1.size();
        int count = 0;
        while(high < n){
            while(low < high && count &&  mpp[s2[high]] == 0){
                if(s1Map[s2[low]] > 0){
                    mpp[s2[low]]++;
                    count--;
                }
                low++;
            }
            if(mpp[s2[high]] > 0){
                count++;
                mpp[s2[high]]--;
            }
            if(count == m) return true;
            high++;
        }
        return false;
    }
};