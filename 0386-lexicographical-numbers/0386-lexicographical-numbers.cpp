class Solution {
public:
    vector<int> lexicalOrder(int n) {
        int i = 1;
        vector<int> res;

        while(i<=n && res.size() < n){
            res.push_back(i);
            if(i*10 <= n ){
                i = (i*10)-1;
            }
            else {
                while((i == n) || i % 10 == 9 ){
                    i = i/10;
                }
            }
            i+=1;
        }
        return res;
    }
};