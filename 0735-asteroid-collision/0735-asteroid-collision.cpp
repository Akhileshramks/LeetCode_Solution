class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        vector<int> res;
        stack<int> st;
        bool flag;
        for(int i =0;i<n;i++){
            int check =  asteroids[i];
            while(!st.empty() && check<0 && st.top()>0){
                if(abs(check)>st.top()){
                    st.pop();
                }
                else if(abs(check) == st.top()){
                    st.pop();
                    check = 0;
                }
                else{
                    check =0;
                }
            }
            if(check!=0){
                st.push(check);
            }
        }

        while(!st.empty()){
            int top = st.top();
            st.pop();
            res.push_back(top);
        }
        reverse(res.begin(),res.end());
        return res;
    }
};