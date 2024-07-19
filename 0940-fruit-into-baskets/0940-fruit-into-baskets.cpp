class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int left = 0;
        int sum = 0;
        unordered_map<int,int> select;
        for(int right = 0;right<n;right++){
            select[fruits[right]]++;
            while(select.size()>2){
                select[fruits[left]]--;
                if(select[fruits[left]]==0){
                    select.erase(fruits[left]);
                }
                left++;
            }
            sum = max(sum,right-left+1);
        }
        return sum;
    }
};