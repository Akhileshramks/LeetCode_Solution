class Solution:
    def minimumCost(self, target: str, words: List[str], costs: List[int]) -> int:
        n = len(target)
        dp = [int(1e9)] * (n + 1)
        dp[0] = 0

        cost = {word: int(1e9) for word in words}
        for word, c in zip(words, costs):
            cost[word] = min(cost[word], c)
        
        for i in range(0,n+1,1):
            for word, c in cost.items():
                word_len = len(word)
                if i >= word_len and target[i - word_len:i] == word:
                    dp[i] = min(dp[i], dp[i - word_len] + c)
        return dp[n] if dp[n] != int(1e9) else -1 
