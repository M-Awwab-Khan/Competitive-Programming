n = int(input())
m = list(map(int, input().split()))
a = list(map(int, input().split()))
tm = list(map(int, input().split()))
ta = list(map(int, input().split()))
m0, a0, dm, da = map(int, input().split())

dp_m = [0 for i in range(n + 1)]
dp_a = [0 for i in range(n + 1)]

dp_m[1] = m0 + m[0]
dp_a[1] = a0 + a[0]

for i in range(2, n + 1):
    dp_m[i] = min(dp_m[i - 1] + m[i - 1], dp_a[i - 1] + ta[i - 1] + m[i - 1])
    dp_a[i] = min(dp_a[i - 1] + a[i - 1], dp_m[i - 1] + tm[i - 1] + a[i - 1])

result = min(dp_m[n] + dm, dp_a[n] + da)
print(result)
