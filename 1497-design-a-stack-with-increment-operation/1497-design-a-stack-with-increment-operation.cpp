class CustomStack {
public:
    vector<int> st;
    vector<int> incrementList;
    int top;
    CustomStack(int maxSize) {
        st.resize(maxSize);
        incrementList.resize(maxSize);
        top = -1;
    }
    
    void push(int x) {
        if(top < (int)(st.size())-1){
            top++;
            st[top] = x;
        }
    }
    
    int pop() {
        if(top <= -1) return -1;
        int res = st[top] + incrementList[top];
        if(top > 0) incrementList[top-1] += incrementList[top];
        incrementList[top] = 0;
        top--;
        return res;
    }
    
    void increment(int k, int val) {
        if(top > -1){
            int limit = min(top , k-1);
            incrementList[limit] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
