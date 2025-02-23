a, b, n = map(int, input().split())


def x(a, b, n):
    for _ in range(n):
        x = a * 10
        smallest_rem = (b - (x % b)) % b
        if smallest_rem < 10:
            a = (a * 10) + smallest_rem
        else:
            print(-1)
            return
    print(x)


x(a, b, n)
