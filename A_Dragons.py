s, n = map(int, input().split())
a = [tuple(map(int, input().split())) for _ in range(n)]
a.sort()

for i in range(n):
    if a[i][0] >= s:
        print("NO")
        break
    s += a[i][1]
else:
    print("YES")
