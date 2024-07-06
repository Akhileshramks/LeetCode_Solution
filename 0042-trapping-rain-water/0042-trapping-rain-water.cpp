class Solution {
public:
    int trap(vector<int>& height) {
        //Using Monotonic Stack to find the previous grater or next greater element and find
        // the height difference between the min(prevGreater,nextGreater) and the height(i)
        int popped;
        stack<int> st;
        int sum = 0;
        int n = height.size();
        int mini = INT_MAX;
        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>height[st.top()]){
                popped = st.top();
                st.pop();
                if(!st.empty()){
                    mini = min(height[st.top()],height[i]) - height[popped];
                    sum +=(mini*(i-st.top()-1));
                }
            }
            st.push(i);
        }
        return sum;
    }
};