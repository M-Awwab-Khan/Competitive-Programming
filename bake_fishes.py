def can_bake_fishes(x, n, k, a, b):
    total_powder_needed = 0
    for i in range(n):
        required = a[i] * x
        if required > b[i]:
            total_powder_needed += required - b[i]
        if total_powder_needed > k:
            return False
    return total_powder_needed <= k

n, k = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

low, high = 0, 1000000
while low < high:
    mid = (low + high + 1) // 2
    if can_bake_fishes(mid, n, k, a, b):
        low = mid
    else:
        high = mid - 1

print(low)
