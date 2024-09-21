class Solution {
public:
    string lds(string s, int n) {
        unordered_set<long long> currHash;
        long long base = 31;
        long long MOD = 1e11 + 7;
        long long hash = 0;
        long long power = 1;

        for (int k = 0; k < n - 1; k++) power = (power * base) % MOD;

        for (int i = 0; i < n; i++) {
            hash = (hash * base + (s[i] - 'a' + 1)) % MOD;
        }
        currHash.insert(hash);

        int m = s.size();
        for (int i = 1; i <= m - n; i++) {
            hash = (hash - (s[i - 1] - 'a' + 1) * power % MOD + MOD) % MOD;
            hash = (hash * base + (s[i + n - 1] - 'a' + 1)) % MOD;
            
            if (currHash.find(hash) != currHash.end()) {
                return s.substr(i, n);
            }
            currHash.insert(hash);
        }

        return "";
    }

    string longestDupSubstring(string s) {
        int n = s.size();
        int low = 1;
        int high = n - 1;
        string res, ans = "";

        while (low <= high) {
            int mid = low + (high - low) / 2;
            res = lds(s, mid);
            if (!res.empty()) {
                ans = res;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};
