t = int(input())
while t:
    t -= 1
    n = int(input())
    nums = list(map(int, input().split()))
    nums.sort()
    total = sum(nums[n-i-1] - nums[i] for i in range(n//2))
    print(total)
