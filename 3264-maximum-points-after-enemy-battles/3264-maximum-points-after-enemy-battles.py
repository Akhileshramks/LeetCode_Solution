class Solution:
    def maximumPoints(self, enemyEnergies: List[int], currentEnergy: int) -> int:
        mini = min(enemyEnergies)
        if(mini>currentEnergy):
            return 0
        sum1 = currentEnergy
        for i in enemyEnergies:
            sum1+=i
        return((sum1-mini)//mini)