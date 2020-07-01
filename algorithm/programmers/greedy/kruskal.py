def find(cycle_table, x):
    if cycle_table[x] == x:
        return x
    return find(cycle_table, cycle_table[x])

def union(cycle_table, x, y):
    x = find(cycle_table, x)
    y = find(cycle_table, y)
    if x < y:
        cycle_table[y] = x
    else:
        cycle_table[x] = y
        

def solution(n, costs):
    answer = 0
    sorted_cost = sorted(costs, key=lambda x: x[2])
    cycle_table = [i for i in range(n)]
    for cost in sorted_cost:
        x = find(cycle_table, cost[0])
        y = find(cycle_table, cost[1])
        if x==y:
            continue
        answer += cost[2]
        union(cycle_table, x, y)
    return answer
