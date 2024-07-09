class Solution:
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        current =0
        sum = 0
        n = len(customers)
        for i,j in customers:
            if current<i:
                current = i
            current += j
            sum+= (current-i)
        return sum/n
