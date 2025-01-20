t = int(input())
while t:
    t -= 1
    n, h = map(int, input().split())
    a = list(map(int, input().split()))

    def slay_dragon(k):
        damage = 0
        for i in range(n - 1):
            damage += min(k, a[i + 1] - a[i])
        damage += k
        return damage >= h

    l = 1
    r = h
    ans = h
    while l <= r:
        mid = (l + r) // 2
        if slay_dragon(mid):
            ans = mid
            r = mid - 1
        else:
            l = mid + 1

    print(ans)
