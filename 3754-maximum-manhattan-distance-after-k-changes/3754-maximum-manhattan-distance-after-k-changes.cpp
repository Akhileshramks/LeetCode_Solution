class Solution {
public:
    int maxDistance(string s, int k) {
        int south = 0, north = 0, east = 0, west = 0;
        int n = s.size();
        int ans = 0;
        for(int i = 0;i < n;i++){
            if(s[i] == 'N') north++;
            else if(s[i] == 'S') south++;
            else if(s[i] == 'E') east++;
            else west++;

            int t1 = min({south, north, k});
            int t2 = min({east, west, k - t1});
            ans = max(ans, abs(south - north) + abs(east - west) + t1 * 2 + t2 * 2);
        }
        return ans;
    }
};