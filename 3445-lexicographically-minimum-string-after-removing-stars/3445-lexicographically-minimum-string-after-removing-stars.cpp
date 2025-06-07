class Solution {
public:
    string clearStars(string s) {
        priority_queue<pair<char, int>, vector<pair<char, int>>, greater<pair<char, int>>> pq;
        int n = s.size();
        unordered_map<int,bool> mpp(n);
        for(int i =0 ;i < n;i++){
            mpp[i] = true;
            if(s[i] == '*'){
                if(!pq.empty()){
                    pair<char,int> top = pq.top();
                    pq.pop();
                    mpp[n - top.second] = false;
                }
                mpp[i] = false;
            }
            else{
                pq.push({s[i],n-i});
            }
        }
        string res = "";
        for(int i = 0;i < n;i++){
            if(mpp[i]) res += s[i];
        }
        return res;
    }
};