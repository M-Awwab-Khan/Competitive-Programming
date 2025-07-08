n, d = map(int, input().split())

if(d == 1):
    print(n + ( n  // 2 ))
else:
    p = (2 * n) // 3

    if(p == 2*(n - p)):
        print(p)
    else:
        print(-1)