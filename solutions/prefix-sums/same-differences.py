from collections import defaultdict
t = int(input())
while t:
    t -= 1
    n = int(input())
    hm = defaultdict(int)
    count = 0
    lst = list(map(int, input().split()))
    for i in range(n):
        if hm[lst[i] - i] > 0:
            count += hm[lst[i] - i]
        hm[lst[i] - i] += 1
    print(count)
