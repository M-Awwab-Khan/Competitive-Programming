t = int(input())
while t:
    t -= 1
    n, k = map(int, input().split())
    str = input()

    curr = str[:k].count("W")
    ans = curr

    for i in range(k, n):
        if str[i - k] == "W":
            curr -= 1
        if str[i] == "W":
            curr += 1
        ans = min(ans, curr)
    print(ans)
