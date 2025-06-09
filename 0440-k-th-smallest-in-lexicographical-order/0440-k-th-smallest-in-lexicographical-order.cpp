class Solution {
public:
    int findKthNumber(int n, int k) {
        int currNum = 1;
        k--;
        while(k > 0){
            int step = countNoOfChildren(n, currNum, currNum + 1);
            if(step > k){
                currNum *= 10;
                k--;
            }
            else{
                currNum++;
                k -= step;
            }
        }
        return currNum;
    }
    int countNoOfChildren(long n, long leftSibling, long rightSibling){
        long count = 0;
        while(leftSibling <= n){
            long right = min((long)n+1, rightSibling);
            long left = leftSibling;
            count += right - left;
            leftSibling *= 10;
            rightSibling *= 10;
        }
        return count;
    }
};