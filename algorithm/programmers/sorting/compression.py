def solution(msg):
    answer = []
    d = {chr(i+64): i for i in range(1, 27)}
    index = 26
    cur_word = ''
    for i in range(len(msg)):
        cur_word += msg[i]
        if i == len(msg) -1:
            answer.append(d[cur_word])
            continue
        if (cur_word + msg[i+1]) in d:
            continue
        answer.append(d[cur_word])
        index += 1
        d[cur_word + msg[i+1]] = index
        cur_word = ''
    return answer
