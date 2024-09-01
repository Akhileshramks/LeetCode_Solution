class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> st;
        int count = 0;
        for(auto i : s){
            if(i == ')'){
                if(!st.empty() && st.top() == '('){
                    st.pop();
                }
                else{
                    count++;
                }
            }
            else{
                st.push(i);
            }
        }
        while(!st.empty()){
            count++;
            st.pop();
        }
        return count;
    }
};