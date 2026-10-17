def count_subarrays_with_at_most_k_distinct(n, k, arr):
    freq = {}
    l = 0
    total = 0

    for r in range(n):
        freq[arr[r]] = freq.get(arr[r], 0) + 1

        while len(freq) > k:
            freq[arr[l]] -= 1
            if freq[arr[l]] == 0:
                del freq[arr[l]]
            l += 1

        total += r - l + 1

    return total


# Example Input
n, k = map(int, input().split())
arr = list(map(int, input().split()))

# Output
print(count_subarrays_with_at_most_k_distinct(n, k, arr))  # Output: 10
