n, x = map(int, input().split())
a = list(map(int, input().split()))

hm = {}
for i in range(n):
    if x - a[i] in hm:
        print(hm[x - a[i]] + 1, i + 1)
        break
    hm[a[i]] = i
else:
    print("IMPOSSIBLE")
