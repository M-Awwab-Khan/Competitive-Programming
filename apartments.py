n, m, k = map(int, input().split())
desired_sizes = list(map(int, input().split()))
sizes = list(map(int, input().split()))

desired_sizes.sort()
sizes.sort()

i = 0
j = 0

ans = 0
while i < n and j < m:
    if abs(desired_sizes[i] - sizes[j]) <= k:
        ans += 1
        i += 1
        j += 1
    elif desired_sizes[i] < sizes[j]:
        i += 1
    else:
        j += 1

print(ans)
