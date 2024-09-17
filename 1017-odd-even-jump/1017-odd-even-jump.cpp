class Solution {
public:
    vector<int> nextGreater(vector<int>& arr,vector<int> original){
        stack<int> st;
        int n = arr.size();
        vector<int> res(n,-1);
        for(auto i : arr){
            while(!st.empty() && st.top() < i){
                res[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        return res;
    }

    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<int> ind;

        for(int i = 0;i<n;i++) ind.push_back(i);
        sort(ind.begin(),ind.end(),[&](const int &a,const int&b){
            if(arr[a] == arr[b]) return a<b;
            return arr[a]<arr[b];
        });

        vector<int> odd = nextGreater(ind,arr);
        sort(ind.begin(),ind.end(),[&](const int &a,const int&b){
            if(arr[a] == arr[b]) return a<b;
            return arr[a]>arr[b];
        });
        vector<int> even = nextGreater(ind,arr);

        vector<vector<int>> dp(n,vector<int>(2,0));
        dp[n-1] = {1,1};
        int count = 0;

        for(int i = n-2;i >= 0;i--){
            if(odd[i] != -1) dp[i][0] = dp[odd[i]][1];
            if(even[i] != -1) dp[i][1] = dp[even[i]][0];
        }
        for(int i =0;i<n;i++) count += dp[i][0];
        return count;
    }
};

/*
                0   1   2   3   4
                10  13  12  14  15

Sort Indices    0   2   1   3   4
Descending      4   3   1   2   0

                0   1   2   3   4
NxtGreat        2   3   3   4   -1
NxtLargest      -1  2   -1  -1  -1


                10
                  \
                   13
                   / \  
                12    14
                        \
                        15   
*/