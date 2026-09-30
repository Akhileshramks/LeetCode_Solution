class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        vector<int> res(n, -1);
        int a = 0, b = 0;
        for(int i = 0;i < n;i++){
            if(seq[i] == '('){
                if(a < b){
                    res[i] = 0;
                    a++;
                }else{
                    res[i] = 1;
                    b++;
                }
            }else{
                if(a < b){
                    res[i] = 1;
                    b--;
                }else{
                    res[i] = 0;
                    a--;
                }
            }
        }
        return res;
    }
};