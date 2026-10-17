n = int(input())
magnets = [input() for i in range(n)]

count = 1
for i in range(n - 1):
    if magnets[i] != magnets[i + 1]:
        count += 1

print(count)
