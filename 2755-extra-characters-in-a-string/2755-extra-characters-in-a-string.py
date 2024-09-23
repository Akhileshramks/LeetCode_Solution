class Solution:
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        wordList = set(dictionary)
        n = len(s)
        dp = [-1]*(n+1)
        def dfs(i):
            if(i == n) :
                return 0
            if(dp[i]!=-1):
                return dp[i]
            res = 1 + dfs(i+1)
            for start in range(i,n):
                if s[i : start+1] in wordList :
                    res = min(dfs(start+1),res)
            dp[i] = res
            return res
        
        return dfs(0)