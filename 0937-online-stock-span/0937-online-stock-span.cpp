
class StockSpanner {
    stack<pair<int,int>> st;
    int count = 0;
    int m;
public:
    StockSpanner() {
        while(!st.empty()) st.pop();
    }
    
    int next(int price) {
        count+=1;
        pair<int,int> new_entry = make_pair(price,count);
        while(!st.empty() && st.top().first<=price){
            st.pop();
        }

        if(!st.empty()){
            m = count-st.top().second; 
        }
        else{
            m = count;
        }
        st.push(new_entry);
        return m;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */