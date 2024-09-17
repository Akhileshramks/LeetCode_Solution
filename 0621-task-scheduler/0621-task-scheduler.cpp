class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char,int> count;
        for(char i : tasks) count[i]++;

        priority_queue<int> pq;
        for(auto i : count) pq.push(i.second);
        int noOfTasks = 0;
        while(!pq.empty()){
            int cycle = n+1;
            vector<int> temp;
            while(cycle-- && !pq.empty()){
                if(pq.top()>1){
                    temp.push_back(pq.top()-1);
                }
                pq.pop();
            }
            for(int i : temp) pq.push(i);
            noOfTasks += !pq.empty() ? n+1 : n-cycle;
        }
        return noOfTasks;
    }
};