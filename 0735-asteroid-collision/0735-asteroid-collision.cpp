class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        for(int i : asteroids){
            int stone = i;
            while(!st.empty() && stone < 0 && st.top() > 0){
                if(st.top() > abs(stone)) stone = 0;
                else if(st.top() == abs(stone)){
                    stone = 0;
                    st.pop();
                }
                else{
                    st.pop();
                }
            }
            if(stone != 0) st.push(stone);
        }
        vector<int> res;
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};