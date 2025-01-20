t = int(input())
while t:
    t -= 1
    n = int(input())
    s = input()
    cnt = n - 1
    for i in range(2, n):
        cnt -= s[i] == s[i-2]
    print(cnt)
