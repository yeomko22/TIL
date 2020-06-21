# bruteforce인지 간파하는 요령은 탐색 범위가 해볼만한 범위인지로 판단
# 이 문제에서 트릭은 문제 조건에 제시된 1-9 사이 중복없는 3자리 숫자라는 조건
# 이를 잘 파악해야만 테스트를 통과할 수 있다.
def gen_candidates():
    candidates = []
    for i in range(1, 10):
        for j in range(1, 10):
            if j==i:
                continue
            for k in range(1, 10):
                if k==j or k==i:
                    continue
                candidates.append(str(i) + str(j) + str(k))
    return candidates

def solution(baseball):
    answer = 0
    candidates = gen_candidates()
    for candidate in candidates:
        flag = True
        for num, strike, ball in baseball:
            num_str = str(num)
            cur_strike = 0
            cur_ball = 0
            for i in range(len(num_str)):
                if num_str[i] == candidate[i]:
                    cur_strike += 1
                elif num_str[i] in candidate:
                    cur_ball += 1
            if cur_strike != strike or cur_ball != ball:
                flag= False
                break
        if flag:
            answer += 1
    return answer
