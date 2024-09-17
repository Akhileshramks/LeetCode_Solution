class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if(n % groupSize != 0 ) return false;
        unordered_map<int,int> count;
        for(auto i : hand) count[i]++;
        priority_queue<int,vector<int>,greater<int>> pq;
        for(auto i : count) pq.push(i.first);
        while(!pq.empty()){
            int start = pq.top();
            for(int next = start;next<start+groupSize;next++){
                if(count.find(next) == count.end()) return false;
                count[next]--;
                if(count[next] == 0){
                    if(pq.top() != next) return false;
                    pq.pop();
                }
            }
        }
        return true;
    }
};