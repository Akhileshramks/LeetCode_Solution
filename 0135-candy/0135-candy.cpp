class Solution {
public:
    int candy(vector<int>& ratings) {
        int i = 1,n = ratings.size();
        int sum = 1;
        while(i < n){
            if(ratings[i-1] == ratings[i]){
                sum += 1;
                i++;
                continue;
            }
            int peak = 1;
            while(i < n && ratings[i-1]<ratings[i]){
                peak++;
                sum += peak;
                i++;
            }
            int down = 1;
            while(i < n && ratings[i-1] > ratings[i]){
                sum += down;
                down++;
                i++;
            }
            if(peak < down) sum += down-peak;
        }
        return sum;
    }
};