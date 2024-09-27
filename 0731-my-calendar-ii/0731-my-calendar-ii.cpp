class MyCalendarTwo {
public:
    vector<pair<int,int>> calender;
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        int count = 0;
        vector<pair<int,int>> overlap;
        pair<int,int> interval;
        cout<<start<<" "<<end<<" ";
        for(auto i : calender){
            if(end > i.first && start < i.second){
                interval = {max(start,i.first),min(end,i.second)};
                cout<<interval.first<<" "<<interval.second<<" ";
                for(auto j : overlap){
                    if(!(interval.second <= j.first || interval.first >= j.second)){
                        return false;
                    }
                }
                overlap.push_back(interval);
            }
        }
        calender.push_back({start,end});
        cout<<endl;
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */