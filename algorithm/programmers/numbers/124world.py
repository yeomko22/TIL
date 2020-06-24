def solution(n):
    answer = ''
    while (n):
        cur_value = n % 3
        if cur_value==0:
            answer += '4'
        else:
            answer += str(cur_value)
        n -= 1
        n = n // 3
    answer = answer[::-1]
    return answer
