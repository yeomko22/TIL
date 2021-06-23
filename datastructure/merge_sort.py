def merge_sort(arr):
    print('sort called', arr)
    if len(arr) == 1:
        return arr
    mid = (len(arr) + 1) // 2
    arr_l = arr[:mid]
    arr_r = arr[mid:]
    l = merge_sort(arr_l)
    r = merge_sort(arr_r)
    return merge(l, r)


def merge(arr_l, arr_r):
    sorted = []
    i = 0
    j = 0
    while True:
        if i + j == len(arr_l) + len(arr_r):
            break
        if i == len(arr_l):
            sorted.append(arr_r[j])
            j += 1
            continue
        if j == len(arr_r):
            sorted.append(arr_l[i])
            i += 1
            continue
        if arr_l[i] < arr_r[j]:
            sorted.append(arr_l[i])
            i += 1
        else:
            sorted.append(arr_r[j])
            j += 1
    print('merge called', arr_l, arr_r, '->', sorted)
    return sorted


if __name__ == '__main__':
    arr = [38, 27, 43, 3, 9, 82, 10]
    sorted_arr = merge_sort(arr)
