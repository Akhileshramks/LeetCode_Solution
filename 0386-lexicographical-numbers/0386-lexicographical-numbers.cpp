class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        int currNum = 1;
        while(res.size() < n){
            res.push_back(currNum);
            if(currNum * 10 <= n){
                currNum *= 10;
            }else{
                while(currNum % 10 == 9 || currNum + 1 > n) currNum /= 10;
                currNum += 1;
            }
        }
        return res;
    }
};