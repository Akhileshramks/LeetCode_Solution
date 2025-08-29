class Solution {
public:
    long long flowerGame(int n, int m) {
        int odd_1 = (n + 1) / 2;
        int even_1 = n - odd_1;
        int odd_2 = (m + 1) / 2;
        int even_2 = m - odd_2;
        long long res = 1ll * odd_1 * even_2 + 1LL * odd_2 * even_1;
        return res;
    }
};