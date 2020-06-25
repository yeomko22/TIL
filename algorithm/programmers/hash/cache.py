def solution(cacheSize, cities):
    answer = 0
    cache = {}
    if not cacheSize:
        return 5 * len(cities)
    
    for city in cities:
        city = city.lower()
        if city in cache:
            answer += 1
            cache[city] = 0
        else:
            answer += 5
            if len(cache) < cacheSize:
                cache[city] = 0
            else:
                cache.pop(sorted(cache, key=lambda x: cache[x], reverse=True)[0])
                cache[city] = 0
        for k in cache:
            cache[k] += 1
    return answer
