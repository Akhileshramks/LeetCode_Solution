class Solution {
public:
    bool canDistribute(int x, vector<int>& quantities, int n) {
        int j = 0;
        int remaining = quantities[j];

        // Loop through each store
        for (int i = 0; i < n; i++) {
            // Check if the remaining quantity of the jth product type
            // can be fully distributed to the ith store
            if (remaining <= x) {
                // If yes, move the pointer to the next product type
                j++;
                // Check if all products have been distributed
                if (j == quantities.size()) {
                    return true;
                } else {
                    remaining = quantities[j];
                }
            } else {
                // Distribute the maximum possible quantity (x) to the ith store
                remaining -= x;
            }
        }
        return false;
    }
    int minimizedMaximum(int n, vector<int>& quantities) {
        // Initialize the boundaries of the binary search
        int left = 0;
        int right = *max_element(quantities.begin(), quantities.end());

        // Perform binary search until the boundaries converge
        while (left < right) {
            int middle = (left + right) / 2;
            if (canDistribute(middle, quantities, n)) {
                // Try for a smaller maximum
                right = middle;
            } else {
                // Increase the minimum possible maximum
                left = middle + 1;
            }
        }
        return left;
    }
};