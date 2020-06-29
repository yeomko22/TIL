def solution(name):
    answer = 0
    moves = [0] * len(name)
    for i, c in enumerate(name):
        moves[i] = min(ord('Z') - ord(c) + 1, ord(c) - ord('A'))
    cur_index = 0
    while True:
        answer += moves[cur_index]
        visited = {cur_index}
        next_moves = [100] * len(moves)
        for i in range(len(moves)):
            if i in visited or i==cur_index or moves[i]==0:
                continue
            next_moves[i] = min(i-cur_index, len(moves) - cur_index + 1)
        print(next_moves)
        break
    print(moves)
    return answer
