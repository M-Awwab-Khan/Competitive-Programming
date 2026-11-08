t = int(input())
while t:
    t -= 1
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    a.sort()
    b.sort(reverse=True)
    al, bl = 0, 0
    ar, br = n - 1, m - 1
    total_sum = 0

    while al <= ar:
        x = abs(a[al] - b[bl])
        y = abs(a[ar] - b[br])
        total_sum += max(x, y)
        if x > y:
            al += 1
            bl += 1
        else:
            ar -= 1
            br -= 1

    print(total_sum)
