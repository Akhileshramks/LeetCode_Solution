class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<int,int> lastSeen;
        int n = s.size();
        for(int i=0;i<n;i++) lastSeen[s[i]-'a'] = i;
        stack<char> st;
        vector<bool> seen(26,false);
        for(int i=0;i<n;i++){
            if(seen[s[i]-'a']) continue;
            seen[s[i]-'a'] = true;
            while(!st.empty() && st.top() > s[i] && i < lastSeen[st.top()-'a']){
                seen[st.top()-'a'] = false;
                st.pop();
            }
            st.push(s[i]);
        }
        string res = "";
        while(!st.empty()){
            res += st.top();
            st.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};