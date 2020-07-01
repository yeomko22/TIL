def solution(n):
    answers = [[], [0]]
    if n == 1:
        return answers[n]
    for i in range(2, n+1):
        left = answers[i-1]
        right = [0 if x==1 else 1 for x in answers[i-1][::-1]]
        answers.append(left + [0] + right)
    return answers[n]
