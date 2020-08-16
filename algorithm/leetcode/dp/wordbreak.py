class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True
        wordset = set(wordDict)
        for i in range(n+1):
            if not dp[i]:
                continue
            for j in range(i+1, n+1):
                substr = s[i:j]
                if substr in wordset:
                    dp[j] = True
        return dp[n]
