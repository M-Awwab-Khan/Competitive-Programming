# eww

n, m = map(int, input().split())
# skip the first digit of each line
a = [set(map(int, input().split()[1:])) for _ in range(n)]
x = a[0]
for i in a:
    x &= i


print(len(x))
