def solution(m, n, board):
    answer = 0
    new_answer = 0
    while True:
        pops = []
        for i in range(1, m):
            for j in range(1, n):
                if board[i][j]=='-':
                    continue
                if board[i-1][j-1]!=board[i-1][j]:
                    continue
                if board[i-1][j-1]!=board[i][j-1]:
                    continue
                if board[i-1][j-1]!=board[i][j]:
                    continue
                pops.append((i, j))
        if not pops:
            break
            
        for pop in pops:
            x, y = pop
            board[x-1] = board[x-1][:y-1] + '--' + board[x-1][y+1:] 
            board[x] = board[x][:y-1] + '--' + board[x][y+1:]

        for i in range(m):
            for j in range(n):
                if board[m-1-i][j] == '-':
                    above = m-i-2
                    while True:
                        if above < 0:
                            break
                        if board[above][j] != '-':
                            board[m-1-i] = board[m-1-i][:j] + board[above][j] + board[m-1-i][j+1:]
                            board[above] = board[above][:j] + '-' + board[above][j+1:]
                            break
                        above -= 1
    for line in board:
        answer += line.count('-')
    return answer
