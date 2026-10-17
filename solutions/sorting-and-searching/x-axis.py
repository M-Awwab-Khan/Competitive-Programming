t = int(input())
while t:
    t -= 1
    nums = list(map(int, input().split()))
    nums.sort()
    print(abs(nums[0] - nums[1]) + abs(nums[2] - nums[1]))
