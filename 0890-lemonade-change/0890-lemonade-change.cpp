class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        vector<int> count(3,0);
        for(auto i:bills){
            if(i == 5){
                count[0]+=1;
            }
            else if(i == 10){
                count[1]+=1;
                if(count[0]){
                    count[0]-=1;
                }
                else{
                    return false;
                }
            }
            else if(i == 20){
                count[2]+=1;
                if(count[1] && count[0]){
                    count[1]-=1;
                    count[0]-=1;
                }
                else if(count[0]>=3){
                        count[0]-=3;
                }
                else{
                    return false;
                }
            }
        }
        return true;
    }
};