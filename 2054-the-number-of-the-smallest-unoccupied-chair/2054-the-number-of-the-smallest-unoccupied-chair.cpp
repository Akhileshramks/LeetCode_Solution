class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        priority_queue<int,vector<int>,greater<int>> seatAvailable;
        

        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> endTime;

        int n = times.size();
        for(int i=0;i<n;i++) seatAvailable.push(i);

        vector<pair<int,int>> timesIndexed;
        for(int i = 0;i<n;i++) timesIndexed.push_back({times[i][0],i});

        sort(timesIndexed.begin(),timesIndexed.end(),[](const pair<int,int>& a,const pair<int,int> &b){
            if(a.first == b.first) return a.second<b.second;
            return a.first < b.first;
        });
        
        for(auto & i : timesIndexed){
            int ind = i.second;
            int indEnd = times[ind][1];
            int start = i.first;
            while(!endTime.empty() && start >= endTime.top().first){
                pair<int,int> end = endTime.top();
                seatAvailable.push(end.second);
                endTime.pop();
            }
            if(ind == targetFriend) return seatAvailable.top();
            int seat = seatAvailable.top();
            seatAvailable.pop();
            endTime.push({indEnd,seat});
        }
        return 0;
    }
};