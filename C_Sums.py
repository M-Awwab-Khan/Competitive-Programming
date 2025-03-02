n = int(input())
sum = 0
for _ in range(n):
    a, b = map(int, input().split())
    sum += ((b - a + 1) * (a + b)) // 2

print(sum)
