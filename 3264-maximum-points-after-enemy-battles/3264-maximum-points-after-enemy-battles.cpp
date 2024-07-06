class Solution {
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        sort(enemyEnergies.begin(),enemyEnergies.end());
        int n = enemyEnergies.size();
        long low = 0;
        long high = n-1;
        long long count = 0;
        while(low<=high){
            if(currentEnergy>=enemyEnergies[low]){
                count+= currentEnergy/enemyEnergies[low];
                currentEnergy = currentEnergy%enemyEnergies[low];
                
            }
            else if(count>0){
                currentEnergy = currentEnergy + enemyEnergies[high];
                high--;
            }
            else{
                break;
            }
        }
        return count;
        
    }
};