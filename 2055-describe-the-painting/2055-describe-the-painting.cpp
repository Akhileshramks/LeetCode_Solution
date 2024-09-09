class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<int,long long> line;
        int start = 1e5,end = 0;
        for(auto i : segments){
            line[i[0]]+=i[2];
            line[i[1]]-=i[2];
            start = min(i[0],start);
            end = max(end,i[1]);
        }
        vector<vector<long long>> res;
        long long sum = line[start];
        int begin = start;
        for(int i = start+1;i<=end+1;i++){
            if(line.find(i)!=line.end()){
                if(sum!=0) res.push_back({begin,i,sum});
                begin = i;
            }
            sum += line[i];
        }
        return res;
    }
};