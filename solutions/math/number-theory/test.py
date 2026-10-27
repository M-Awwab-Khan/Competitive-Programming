t = int(input())

for _ in range(t):
    n = int(input())
    arr = map(int, list(input().split()))

    ans = 1
    for i in arr:
        ans = ans * i % 1000000007
    print(ans)
