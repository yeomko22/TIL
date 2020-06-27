from itertools import combinations

def solution(relation):
    answer = 0
    indexs = [i for i in range(len(relation[0]))]
    combs = []
    for i in range(1, len(indexs)+1):
        cur_combs = combinations(indexs, i)
        for comb in cur_combs:
            combs.append(set(comb))
    
    while combs:
        cur_comb = combs.pop(0)
        records = set()
        for i in range(len(relation)):
            record = []
            for col in cur_comb:
                record.append(relation[i][col])
            records.add(tuple(record))
        if len(records)==len(relation):
            answer += 1
            new_combs = []
            for comb in combs:
                if cur_comb.intersection(comb)==cur_comb:
                    continue
                new_combs.append(comb)
            combs = new_combs
    return answer
