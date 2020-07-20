# 가장 빨리 끝나는 구간부터 넣어주면 해결 쌉가능

def solution(A, B):
    if not A and not B:
        return 0
    intervals = []
    for i in range(len(A)):
        intervals.append((B[i] - A[i], (A[i], B[i])))
    intervals = sorted(intervals, key=lambda x:x[1][1])
    cur_interval = intervals[0]
    answer = 1
    for i in range(1, len(intervals)):
        if (intervals[i][1][0] > cur_interval[1][1]):
            answer += 1
            cur_interval = intervals[i]
    return answer
