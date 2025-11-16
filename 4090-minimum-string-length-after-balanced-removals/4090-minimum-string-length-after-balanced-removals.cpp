class Solution {
public:
    int minLengthAfterRemovals(string s) {
        int aCount = 0, bCount = 0;
        int n = s.size();
        for(int i = 0;i < n;i++){
            if(s[i] == 'a') aCount++;
            else bCount++;
        }

        return abs(aCount - bCount);
    }
};