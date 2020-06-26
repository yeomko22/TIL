import re

def solution(files):
    num_pattern = re.compile(r'\d+')
    tmp = []
    for file in files:
        num_start, num_end = re.search(num_pattern, file).span()
        head = file[:num_start]
        number = file[num_start:num_end]
        tmp.append((head.lower(), int(number), file))
    sorted_files = sorted(tmp, key=lambda x: (x[0], x[1]))
    answer = [x[2] for x in sorted_files]
    return answer
