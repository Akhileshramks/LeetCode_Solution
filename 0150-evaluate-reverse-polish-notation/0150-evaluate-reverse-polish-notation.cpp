class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        int n = tokens.size();
        int ans,a,b;
        for(int i = 0;i<n;i++){
            string m = tokens[i];
            if(m == "+"){
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                ans = a+b;
                st.push(ans);
            }
            else if (m == "-"){
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                ans = b-a;
                st.push(ans);
            }else if (m == "*"){
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                ans = b*a;
                st.push(ans);
            }else if (m == "/"){
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                ans = b/a;
                st.push(ans);
            }else{
                st.push(stoi(tokens[i]));
            }
        }
        return st.top();
    }
};