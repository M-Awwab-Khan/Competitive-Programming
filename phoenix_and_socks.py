from collections import Counter

t = int(input())
while t:
    t -= 1

    n, l, r = map(int, input().split())
    socks = list(map(int, input().split()))

    cost = 0
    cost += abs((n // 2) - l)
    lsocks = socks[: n // 2]
    rsocks = socks[n // 2 :]

    lsockshm = Counter(lsocks)
    rsockshm = Counter(rsocks)

    for sock in lsockshm:
        if sock in rsockshm:
            common = min(lsockshm[sock], rsockshm[sock])
            lsockshm[sock] -= common
            rsockshm[sock] -= common

        if lsockshm[sock] > 0:
            cost += lsockshm[sock]
    print(cost)
