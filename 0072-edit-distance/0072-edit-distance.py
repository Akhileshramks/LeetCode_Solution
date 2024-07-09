class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n = len(word1)
        m = len(word2)
        prev = [i for i in range(m+1)]
        curr = [0]*(m+1)
        for i in range(1,n+1):
            curr[0] = i
            for j in range(1,m+1):
                if(word1[i-1] == word2[j-1]):
                    curr[j] = prev[j-1]
                else:
                    curr[j] = (min([curr[j-1],prev[j-1],prev[j]])+1)
            prev = curr[:]
        return prev[m]
