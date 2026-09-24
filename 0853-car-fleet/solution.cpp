class Solution {
public:
    static bool positionComparator(const pair<int, double> &a, const pair<int, double> &b){
        return a.first < b.first;
    }
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, double>> timeTaken;
        for(int i = 0;i < position.size();i++){
            timeTaken.push_back({position[i], (double)(target - position[i])/ speed[i]});
        }
        sort(timeTaken.begin(), timeTaken.end(), positionComparator);

        stack<double> destTime;
        for(int i = 0;i < timeTaken.size(); i++){
            while(!destTime.empty() && timeTaken[i].second >= destTime.top()) destTime.pop();
            destTime.push(timeTaken[i].second);
        }
        return destTime.size();
    }
};