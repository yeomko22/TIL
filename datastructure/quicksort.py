def partition(arr, low, high):
    i = (low - 1)
    pivot = arr[high]
    for j in range(low, high):
        if arr[j] <= pivot:
            i = i+1
            print('pivot', pivot, 'swap, i:', i, arr[i], 'j:', j, arr[j])
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    print('after partition', arr)
    return i + 1


def quick_sort(arr, low, high):
    if len(arr) == 1:
        return arr
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)


if __name__ == '__main__':
    arr = [38, 27, 43, 3, 9, 82, 10]
    quick_sort(arr, 0, len(arr)-1)
    print('sorted', arr)
