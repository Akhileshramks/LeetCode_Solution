class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        long long sum = accumulate(skill.begin(),skill.end(),0);
        int n = skill.size();
        if(sum % (1ll*(n/2)) != 0) return -1;
        unordered_map<int,int> mpp;
        long long res = 0;
        long long target = sum / (1ll * (n/2));
        for(auto &i : skill) mpp[i]++;
        for(auto &i : skill){
            if(mpp[i] > 0 && mpp[target-i]>0){
                res += (i * (target-i));
                mpp[i]--;
                mpp[target-i]--;
            }
            else if(mpp[i] > 0 || mpp[target-i] >0 ){
                return -1;
            }
        }
        return res;
    }
};