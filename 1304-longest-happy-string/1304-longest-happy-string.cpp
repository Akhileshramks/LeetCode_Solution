class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int,char>> pq;
        if(a > 0) pq.push({a,'a'});
        if(b > 0) pq.push({b,'b'});
        if(c > 0) pq.push({c,'c'});
        string res = "";
        while(!pq.empty()){
            pair<int,char> m = pq.top();
            pq.pop();
            int count = m.first;
            int letter = m.second;
            if(res.size() >= 2 && res[res.size()-1] == letter && res[res.size()-2] == letter){
                if(pq.empty()) break;
                pair<int,char> next = pq.top();
                pq.pop();
                res += next.second;
                next.first--;
                if(next.first > 0) pq.push(next);
            }
            else{
                res += letter;
                count--;
            }
            if(count > 0) pq.push({count,letter});
        }
        return res;
    }
};