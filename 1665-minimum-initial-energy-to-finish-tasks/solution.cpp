class Solution {
public:
    static bool comparator(vector<int> a, vector<int> b){
        int diff1 = a[1] - a[0];
        int diff2 = b[1] - b[0];
        if(diff1 == diff2) return b[1] < a[1];
        if(diff1 > diff2) return true;
        return false;
    }
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), comparator);
        int res = 0;
        int scoreAdded = 0;
        for(auto i : tasks){
            if(i[1] <= res) res -= i[0];
            else{
                scoreAdded += i[1] - res;
                res += i[1] - res - i[0];
            }
        }
        return scoreAdded;
    }
};
/*
score = 12, res = 2
score = 14, res = 2
score = 15, res 
*/

