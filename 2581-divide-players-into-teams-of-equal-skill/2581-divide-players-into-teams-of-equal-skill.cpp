class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        long long sum = accumulate(skill.begin(),skill.end(),0);
        int n = skill.size();
        if(sum % (1ll*(n/2)) != 0) return -1;
        sort(skill.begin(),skill.end());
        int low = 0;
        int high = n-1;
        long long target = sum / ((n/2)*1ll);
        cout<< target;
        long long res = 0;
        while(low < high){
            if(skill[low] + skill[high] == target){
                res += (skill[low] * skill[high]);
            }
            else{
                return -1;
            }
            low++;
            high--;
        }
        return res;
    }
};