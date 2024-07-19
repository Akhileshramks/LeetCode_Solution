from typing import List

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        # Initialize distances array with "infinity"
        dp = [[float('inf')] * n for _ in range(k + 2)]
        dp[0][src] = 0
        
        for i in range(1, k + 2):
            for u, v, w in flights:
                dp[i][v] = min(dp[i][v], dp[i - 1][u] + w)
        
        # Find the minimum cost to reach dst within k stops (k+1 edges)
        ans = min(dp[i][dst] for i in range(k + 2))
        
        return -1 if ans == float('inf') else ans

# Example usage:
# solution = Solution()
# result = solution.findCheapestPrice(n, flights, src, dst, k)
# print(result)
