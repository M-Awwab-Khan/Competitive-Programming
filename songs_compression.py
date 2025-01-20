n, m = map(int, input().split())
sizes = []
compressed_sizes = []
for _ in range(n):
    a, b = map(int, input().split())
    sizes.append(a)
    compressed_sizes.append(b)


differences = []
for i in range(n):
    differences.append(sizes[i] - compressed_sizes[i])

differences.sort(reverse=True)

if sum(compressed_sizes) > m:
    print(-1)
    exit()

if sum(sizes) <= m:
    print(0)
    exit()

total_size = sum(sizes)
count = 0
for i in range(n):
    if total_size - differences[i] <= m:
        print(count + 1)
        exit()
    total_size -= differences[i]
    count += 1
print(-1)
