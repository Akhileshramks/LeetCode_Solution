class Solution {
public:
    int maximumSwap(int num) {
        string m = to_string(num);
        int n = m.size();
        int i = n-2;
        int ind = n-1,finalInd2 = 0,finalInd1 = 0;
        while(i >= 0){
            if(m[ind] < m[i]){
                ind = i;
            }
            else if(m[i] < m[ind]){
                finalInd1 = i;
                finalInd2 = ind;
            }
            i--;
        }
        swap(m[finalInd1],m[finalInd2]);
        return stoi(m);
    }
};