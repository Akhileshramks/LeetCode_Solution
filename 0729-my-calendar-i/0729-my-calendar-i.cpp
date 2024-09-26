class MyCalendar {
public:
    vector<pair<int,int>> event;
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        if(start > end) return false;
        int n = event.size();
        bool flag = true;
        for(int i = 0; i < n; i++){
            if(!((event[i].first >= end || event[i].second <= start))){
                flag = false;
            }
        }
        if(flag){
            event.push_back({start,end});
        }
        return flag;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */