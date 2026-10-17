n, a, b = map(int, input().split())
n = n - a
x = n - b
if x <= 0:
    print(n)
else:
    print(n - x + 1)
