class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m = len(grid)
        n = len(grid[0])
        visited = [[False for i in range(n)] for j in range(m) ]
        st = deque()
        island =0
        for i in range(m):
            for j in range(n):
                if(grid[i][j] == "1" and not visited[i][j]):
                    island+=1
                    st.append((i,j))
                    while st:
                        x,y = st.pop()
                        visited[x][y] = True
                        for dx,dy in [(1,0),(0,1),(-1,0),(0,-1)]:
                            xx = x+dx
                            yy = y+dy
                            if(xx<0 or xx>=m or yy<0 or yy>=n):
                                continue
                            if(not visited[xx][yy] and grid[xx][yy]=="1"):
                                st.append((xx,yy))
        return island        