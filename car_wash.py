def solve():
    n = int(input())
    e1, e2 = map(int, input().split())

    a1 = [0] * (n + 1)
    temp = list(map(int, input().split()))
    for i in range(1, n + 1):
        a1[i] = temp[i - 1]

    a2 = [0] * (n + 1)
    temp = list(map(int, input().split()))
    for i in range(1, n + 1):
        a2[i] = temp[i - 1]

    s12 = [0] * (n)
    temp = list(map(int, input().split()))
    for i in range(1, n):
        s12[i] = temp[i - 1]

    s21 = [0] * (n)
    temp = list(map(int, input().split()))
    for i in range(1, n):
        s21[i] = temp[i - 1]

    x1, x2 = map(int, input().split())

    dp1 = [0] * (n + 1)
    dp2 = [0] * (n + 1)

    dp1[0] = e1
    dp2[0] = e2

    dp1[1] = e1 + a1[1]
    dp2[1] = e2 + a2[1]

    for i in range(2, n + 1):
        dp1[i] = min(dp1[i - 1] + a1[i], dp2[i - 1] + s21[i - 1] + a1[i])
        dp2[i] = min(dp2[i - 1] + a2[i], dp1[i - 1] + s12[i - 1] + a2[i])

    dp1[n] += x1
    dp2[n] += x2

    print(min(dp1[n], dp2[n]))


t = int(input())
while t:
    t -= 1
    solve()
