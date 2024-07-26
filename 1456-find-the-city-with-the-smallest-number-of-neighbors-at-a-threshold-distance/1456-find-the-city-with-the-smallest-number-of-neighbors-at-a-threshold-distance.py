class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        dist = [[int(1e9)]*n for _ in range(n)]
        for i in range(n):
            dist[i][i] = 0
        for i,j,w in edges:
            dist[i][j] = w
            dist[j][i] = w
        
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j])
                
        mini = int(1e9)
        m = -1
        for i in range(n):
            cnt = 0
            for j in range(n):
                if(i!=j and dist[i][j]<=distanceThreshold):
                    cnt+=1
            if(cnt<=mini):
                mini = cnt
                m = i
        return m