class Solution {
public:
    string clearDigits(string s) {
        stack<char> st;
        for(char i : s){
            if(i >= '0' && i <='9' && !st.empty()) st.pop();
            else st.push(i); 
        }
        string n = "";
        while(!st.empty()){
            n += st.top();
            st.pop();
        }
        reverse(n.begin(), n.end());
        return n;
    }
};