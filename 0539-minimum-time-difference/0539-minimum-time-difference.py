class Solution:
    def findMinDifference(self, timePoints: List[str]) -> int:
        ls = []
        for i in timePoints:
            m = i.split(":")
            ls.append(int(m[0])*60 + int(m[1]))
        ls.sort()
        mini = 1440 - ls[-1] + ls[0]
        for i in range(1,len(ls)):
            mini = min(ls[i]-ls[i-1],mini)
        return mini