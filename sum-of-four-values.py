n, x = map(int, input().split())
arr = list(map(int, input().split()))
pair_sums = {}

for i in range(n):
    for j in range(i + 1, n):
        pair_sum = arr[i] + arr[j]
        if pair_sum not in pair_sums:
            pair_sums[pair_sum] = []
        pair_sums[pair_sum].append((i, j))

for pair_sum in pair_sums:
    complement = x - pair_sum
    if complement in pair_sums:
        for a, b in pair_sums[pair_sum]:
            for c, d in pair_sums[complement]:
                if len(set([a, b, c, d])) == 4:
                    print(a + 1, b + 1, c + 1, d + 1)
                    exit()

print("IMPOSSIBLE")
