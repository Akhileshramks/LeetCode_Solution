class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if(n % groupSize != 0) return false;
        unordered_map<int,int> count;
        for(int i : hand) count[i]++;
        for(int i : hand){
            int start = i;
            while(count[start-1]) start--;
            while(start<=i){
                while(count[start]){
                    for(int next = start;next<start+groupSize;next++){
                        if(count[next] == 0) return false;
                        count[next]--;
                    }
                }
                start++;
            }
        }
        return true;
    }
};