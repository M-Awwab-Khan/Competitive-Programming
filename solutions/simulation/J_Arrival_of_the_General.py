n = int(input())
a = list(map(int, input().split()))

maxi = a.index(max(a))

mini = maxi
for i in range(n):
    if a[i] <= a[mini]:
        mini = i

if maxi > mini:
    swaps = maxi + (n - mini - 2)
else:
    swaps = maxi + (n - mini - 1)

print(swaps)
