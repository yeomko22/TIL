def solution(land):
    dp = land[0]
    for i in range(1, len(land)):
        new_dp = []
        for j in range(len(dp)):
            new_dp.append(land[i][j] + max(dp[:j] + dp[j+1:]))
        dp = new_dp
    return max(dp)
