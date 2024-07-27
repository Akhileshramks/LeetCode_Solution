
class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        if(len(source)!=len(target)):
            return -1
        
        distance = [ [float('inf')]*26 for i in range(26)]
        for i in range(len(original)):
            distance[ord(original[i])-ord('a')][ord(changed[i])-ord('a')] = min(cost[i], distance[ord(original[i])-ord('a')][ord(changed[i])-ord('a')])

        for k in range(26):
            for i in range(26):
                for j in range(26):
                    distance[i][j] = min(distance[i][j],distance[i][k]+distance[k][j])

        cost_to_change = 0

        for i in range(len(source)):
            if(source[i] == target[i]):
                continue
            elif(distance[ord(source[i])-ord('a')][ord(target[i])-ord('a')]!=float('inf')):
                cost_to_change += distance[ord(source[i])-ord('a')][ord(target[i])-ord('a')]
            else:
                print(source[i],target[i])
                return -1
            
        return cost_to_change
