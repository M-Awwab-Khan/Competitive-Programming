t = int(input())
while t:
    t -= 1
    n = int(input())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    diff = [y[i] - x[i] for i in range(n)]

    diff.sort()

    left = 0
    right = n - 1
    days = 0

    while left < right:
        if diff[left] + diff[right] >= 0:
            days += 1
            left += 1
            right -= 1
        else:
            left += 1

    print(days)
