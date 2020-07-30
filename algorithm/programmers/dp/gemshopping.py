from collections import Counter

def solution(gems):
    unique_gems = set(gems)
    start = 0
    c = Counter()
    candidates = []
    answer = [0, 0]
    min_interval = 100001
    for i, gem in enumerate(gems):
        c[gem] += 1
        if len(c.keys()) == len(unique_gems):
            while True:
                if c[gems[start]] > 1:
                    c[gems[start]] -= 1
                    start += 1
                else:
                    break
            if (i - start) < min_interval:
                answer = [start+1, i+1]
                min_interval = i - start
    return answer
