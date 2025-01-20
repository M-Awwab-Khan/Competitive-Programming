n, s = map(int, input().split())
nums = list(map(int, input().split()))

minlen = float("inf")
i = sm = 0
for j in range(len(nums)):
    sm += nums[j]
    while sm >= s:
        minlen = min(minlen, j - i + 1)
        sm -= nums[i]
        i += 1


print(minlen if minlen != float("inf") else 0)
