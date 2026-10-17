from math import comb

tt = int(input())

while tt:
    tt -= 1
    n, t, m = map(int, input().split())

    mn = n * m
    if m == 0:
        if t == 0:
            print(1)
            continue
        else:
            print(0)

    elif n == 0:
        if m == 0 and t == 0:
            print(1)
            continue
        else:
            print(0)
            continue

    if t < mn:
        print(0)
    else:
        k = t - mn  # req
        print(comb(n + k - 1, n - 1))
