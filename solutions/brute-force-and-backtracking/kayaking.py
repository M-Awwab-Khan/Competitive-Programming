n = int(input())
weights = list(map(int, input().split()))

weights.sort()
min_instability = float("inf")
for i in range(2 * n):
    for j in range(i + 1, 2 * n):
        remaining = [weights[k] for k in range(2 * n) if k != i and k != j]

        instability = 0
        for k in range(0, len(remaining), 2):
            instability += abs(remaining[k] - remaining[k + 1])

        min_instability = min(min_instability, instability)
print(min_instability)
