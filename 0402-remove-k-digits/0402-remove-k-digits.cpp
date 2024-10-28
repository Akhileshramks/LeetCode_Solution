class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        for(char i : num){
            while(!st.empty() && k > 0 && i < st.top()){
                st.pop();
                k--;
            }
            st.push(i);
        }
        while(!st.empty() && k){
            st.pop();
            k--;
        }
        string res;
        while(!st.empty()){
            res += st.top();
            st.pop();
        }
        int i = 0;
        reverse(res.begin(),res.end());
        while(res[i] == '0') i++;
        res = res.substr(i);
        return res.size() == 0 ? "0" : res;
    }
};