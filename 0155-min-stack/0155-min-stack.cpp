class MinStack {
    stack<long long> st;
    long long mini;
public:
    MinStack() {
        while(!st.empty()) st.pop();
        long mini = INT_MAX;
    }
    
    void push(long val) {
        if(st.empty()){
            mini = val;
            st.push(val);
        }
        else{
            if(val>mini){
                st.push(val);
            }
            else{
                st.push(2*val-mini);
                mini = val;
            }
        }
    }
    void pop() {
        long long del = st.top();
        if(del>mini){
        }
        else{
            mini = 2*mini-del;
        }
        st.pop();
    }
    
    int top() {
        long m = st.top();
        if(m>mini) return m;
        else return mini;
    }
    
    int getMin() {
        return mini;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */