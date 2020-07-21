# 너무 기초적인 실수함. 역시 졸린 상태에서 푸는 알고리즘이 한번에 맞을리가 없음
# 역시 정규표현식과 문자열 처리 문제는 파이썬으로 푸는게 제일 깔끔한거 같다.
import re

def solution(S):
    words = S.split(' ')
    answer = -1
    re_num = re.compile(r'[0-9]')
    re_char = re.compile(r'[a-zA-Z]')
    for word in words:
        num_cnt = 0
        char_cnt = 0
        flag = True
        for c in word:
            if re.match(re_num, c):
                num_cnt += 1
            elif re.match(re_char, c):
                char_cnt += 1
            else:
                flag = False
                break
        if flag and num_cnt%2==1 and char_cnt%2==0:
            answer = max(answer, len(word))
    return answer
