class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());
        int n = asteroids.size();\
        long long sum = mass;
        for(int i = 0;i < n;i++){
            if(asteroids[i] <= sum) sum = min(1LL * asteroids[i] + sum, (long long)INT_MAX);
            else return false;
        }
        return true;
    }
};