def solution(dartResult):
    darts = []
    cur_dart = ''
    for i in range(len(dartResult) - 1):
        cur_dart += dartResult[i]
        if not dartResult[i].isnumeric() and dartResult[i+1].isnumeric():
            darts.append(cur_dart)
            cur_dart = ''
    darts.append(cur_dart + dartResult[-1])
    scores = []
    for i in range(len(darts)):
        score = ''
        bonus = ''
        option = ''
        for c in darts[i]:
            if c.isnumeric():
                score += c
            elif c=='#' or c=='*':
                option += c
            else:
                bonus += c
        score = int(score)
        if bonus=='D':
            score = score * score
        elif bonus=='T':
            score = score * score * score
        if option=='#':
            score = -1 * score
        elif option=='*':
            if i > 0:
                scores[i-1] = scores[i-1] * 2
            score = score * 2
        scores.append(score)
    answer = sum(scores)
    return answer
