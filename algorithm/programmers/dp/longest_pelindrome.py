"""
조심해야할 포인트는 문자열 길이가 1, 2일때 예외처리를 해주는 부분과
바로 앞뒤로 동일한 문자가 등장하는 부분을 미리 처리해주는 것
"""

def solution(s):
    if len(s)==1:
        return 1
    if len(s)==2:
        if s[0]==s[1]:
            return 2
        else:
            return 1
    answer = 0
    dp = []
    for i in range(len(s)):
        dp.append([0]*len(s))
        dp[i][i] = 1
    for i in range(1, len(s)):
        if s[i]==s[i-1]:
            dp[i-1][i]=1
    for j in range(len(s)):
        for i in range(0, j-1):
            if dp[i][j]==1:
                continue
            if s[j]==s[i] and dp[i+1][j-1]==1:
                dp[i][j] = 1
                answer = max(answer, j-i+1)
    return answer
