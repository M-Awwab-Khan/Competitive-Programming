n = int(input())

dp = [0] * (10001)
dp[1] = 0
dp[2] = 0
dp[3] = 1

if n == 1:
    print(0)
    exit()
elif n == 2:
    print(0)
    exit()
elif n == 3:
    print(1)
    exit()

for i in range(4, 10001):
    for j in range((i//2) + 1, i):
        if dp[j] == 0:
            dp[i] = 1
            break

if (dp[n] == 0):
    print(0)
else:
    for i in range((n//2) + 1, n + 1):
        if (dp[i] == 0):
            print(n-i)
            exit()
