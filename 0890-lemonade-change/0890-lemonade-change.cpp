class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int count5 = 0,count10  = 0,count20 = 0;
        for(auto &i : bills){
            if(i == 5) count5++;
            else if(i == 10){
                count10++;
                if(count5 > 0) count5--;
                else return false;
            }
            else{
                count20++;
                if(count10 > 0 && count5 > 0) count5--,count10--;
                else if(count5>=3) count5-=3;
                else return false;
            }
        }
        return true;
    }
};