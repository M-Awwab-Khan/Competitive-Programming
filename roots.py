n, q = map(int, input().split())
roots = map(int, input().split())
queries = [int(input()) for _ in range(q)]


roots = sorted(roots)

def binarySearch(arr, x):
    left = 0
    right = n - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == x:
            return -1
        elif arr[mid] < x:
            left = mid + 1
        else:
            right = mid - 1
    return left


for query in queries:
    idx = binarySearch(roots, query)
    print(idx)
    if idx == -1:
        print(0)
    elif ( n - idx ) % 2 == 0:
        print("POSTIVE")
    else:
        print("NEGATIVE")
