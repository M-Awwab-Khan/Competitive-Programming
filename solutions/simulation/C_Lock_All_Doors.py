n, k = map(int, input().split())
a = "".join(list(map(str, input().split())))

i = a.find("0")
j = a.rfind("0")

if i == -1:
    print(0)
else:
    ans = 0
    if k < i:
        ans += 2 * (i - k)
    if k > j + 1:
        ans += 2 * (k - (j + 1))

    # print(i, j)
    for x in range(i, j + 1):
        ans += 1
        if a[x] == "1":
            ans += 1
    print(ans)
