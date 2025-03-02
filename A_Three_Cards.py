n = int(input())
nums = [int(x) for x in input().split()]
nums.sort(reverse=True)

ans = str(nums[0]) + str(nums[1]) + str(nums[2])
print(ans)
# wa
