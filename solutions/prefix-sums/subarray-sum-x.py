def count_subarrays_with_sum(n, x, arr):
    pref_sums = {0: 1}
    pref = 0
    cnt = 0

    # Calculate the prefix sum at every index, and find the
    # count of subarrays with sum = pref - X
    for i in range(n):
        pref += arr[i]
        cnt += pref_sums.get(pref - x, 0)
        pref_sums[pref] = pref_sums.get(pref, 0) + 1

    return cnt


# Input
n, x = map(int, input().split())
arr = list(map(int, input().split()))

# Output
print(count_subarrays_with_sum(n, x, arr))
