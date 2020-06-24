def solution(routes):
    answer = 0
    routes.sort()
    prev = routes[0]
    for i in range(1, len(routes)):
        if routes[i][0] > prev[1]:
            answer += 1
            prev = routes[i]
        else:
            prev[0] = max(prev[0], routes[i][0])
            prev[1] = min(prev[1], routes[i][1])
    answer += 1
    return answer
