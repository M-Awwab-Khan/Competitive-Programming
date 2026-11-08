t = int(input())
while t:
    t -= 1
    n = int(input())
    nums = list(map(int, input().split()))

    nums.sort()
    l = 0
    r = n - 1

    cost = 0
    while l < r:
        cost += nums[r] - nums[l]
        l += 1
        r -= 1

    print(cost)
