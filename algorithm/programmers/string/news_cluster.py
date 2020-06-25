import re
from collections import Counter

re_alphabet = re.compile(r'[^A-Z]')

def preprocess(input_str):
    input_str = input_str.upper()
    return re.sub(re_alphabet, ' ', input_str)

def tokenize(input_str):
    tokens = []
    for i in range(1, len(input_str)):
        token = input_str[i-1:i+1]
        if ' ' in token:
            continue
        tokens.append(token)
    return tokens

def zakade(tokens1, tokens2):
    counter1 = Counter(tokens1)
    counter2 = Counter(tokens2)
    union_count = sum(counter1.values()) + sum(counter2.values())
    intersect_count = 0
    for key in counter1:
        intersect = min(counter1[key], counter2[key])
        intersect_count += intersect
        union_count -= 2 * intersect
    union_count += intersect_count
    if not union_count:
        return 65536
    zakade = int((intersect_count / union_count) * 65536)
    return zakade

def solution(str1, str2):
    str1 = preprocess(str1)
    str2 = preprocess(str2)
    tokens1 = tokenize(str1)
    tokens2 = tokenize(str2)
    answer = zakade(tokens1, tokens2)
    return answer
