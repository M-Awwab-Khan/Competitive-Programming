t = int(input())
while t:
    t -= 1

    n = int(input())
    nums = list(map(int, input().split()))

    snums = sorted(nums)
    for i in range(n):
        if nums[i] % 2 != snums[i] % 2:
            print("NO")
            break
    else:
        print("YES")

    # for l in range(n - 1):
    #     for r in range(l + 1, n):
    #         if (nums[l] % 2 == nums[r] % 2) and nums[r] < nums[l]:
    #             nums[l], nums[r] = nums[r], nums[l]


    # for i in range(n - 1):
    #     if nums[i] > nums[i + 1]:
    #         print("NO")
    #         break
    # else:
    #     print("YES")
