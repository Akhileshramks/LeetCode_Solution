class Solution {
public:
    int minDeletions(string s) {
        vector<int> freq(26);
        for(int i = 0;i < s.size();i++){
            freq[s[i] - 'a']++;
        }
        priority_queue<int,vector<int>> pq;
        for(int i = 0;i < 26;i++){
            if(freq[i] > 0) pq.push(freq[i]);
        }
        int ans = 0;
        while(!pq.empty()){
            int p = pq.top();
            pq.pop();
            while(!pq.empty() && pq.top() == p){
                int q = pq.top();
                pq.pop();
                if(q-1 > 0){
                    pq.push(q-1);
                    ans++;
                }else{
                    ans += 1;
                }
            }
        }
        return ans;
    }
}; 