
class Solution:
    def toposort(self,adj,k):
        res = []
        indegree = [0]*k
        for i in range(k):
            for j in adj[i]:
                indegree[j]+=1
        q = deque()
        for i in range(k):
            if(indegree[i] == 0):
                q.append(i)
                indegree[i]-=1
        while(q):
            front = q.popleft()
            res.append(front)
            for i in adj[front]:
                indegree[i]-=1
                if(indegree[i]==0):
                    q.append(i)
                    indegree[i] = -1
        return res
    def buildMatrix(self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]) -> List[List[int]]:
        adjRow = [[] for i in range(k)]
        adjCol = [[] for i in range(k)]
        for i,j in rowConditions:
            adjRow[i-1].append(j-1)
        for i,j in colConditions:
            adjCol[i-1].append(j-1)
        rowIndex = self.toposort(adjRow,k)
        if(len(rowIndex)!=k):
            return []
        colIndex = self.toposort(adjCol,k)
        if(len(colIndex)!=k):
            return []
        matrix = [[0 for i in range(k)] for j in range(k)]
        for rind in range(k):
            for cind in range(k):
                if(rowIndex[rind] == colIndex[cind]):
                    matrix[rind][cind] = rowIndex[rind]+1
        return matrix
        
        