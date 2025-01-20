n = int(input())
nums = list(map(int, input().split()))

nums.sort()
min_diff = float("inf")
for i in range(n - 1):
    min_diff = min(min_diff, abs(nums[i] - nums[i + 1]))

results = []
for i in range(n - 1):
    if abs(nums[i] - nums[i+1]) == min_diff:
        results.extend([nums[i], nums[i+1]])

for num in results:
    print(num, end=" ")
