class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> operation;
        stack<char> st;
        for(char i : expression){
            if(i == '!' || i == '&' || i == '|') operation.push(i);
            else if(i != ',' && i != ')') st.push(i);
            else if(i == ')'){
                char op = operation.top();
                operation.pop();
                int res = op == '&' ? 1 : 0;
                while(st.top() != '('){
                    int value = st.top() == 't' ? 1 : 0;
                    st.pop();
                    if(op == '&') res &= value;
                    else if(op == '|') res |= value;
                    else if(op == '!') res = !value;
                }
                st.pop();
                char p = res == 1 ? 't' : 'f';
                st.push(p);
            }
        }
        if(st.top() == 't') return true;
        return false;
    }
    
};