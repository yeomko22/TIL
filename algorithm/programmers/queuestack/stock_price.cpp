def solution(prices):
    answer = [0] * len(prices)
    stack = [(0, prices[0])]
    for i in range(1, len(prices)):
        while True:
            if not stack or prices[i] >= stack[-1][1]:
                stack.append((i, prices[i]))
                break
            pop_index, pop_price = stack.pop()
            answer[pop_index] = i - pop_index
    while stack:
        pop_index, pop_price = stack.pop()
        answer[pop_index] = len(prices) -1 - pop_index
    return answer
