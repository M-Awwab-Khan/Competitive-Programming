# t = int(input())
# while t:
#     t -= 1

#     n, k = list(map(int, input().split()))
#     nums = list(map(int, input().split()))

#     nums.sort()

#     sm = sum(nums)
#     mins = 0
#     maxes = 0
#     for i in range(k):
#         if nums[mins] + nums[mins + 1] < nums[-1-maxes]:
#             sm -= nums[mins] + nums[mins + 1]
#             mins += 2
#         else:
#             sm -= nums[-1 - maxes]
#             maxes += 1

#     print(sm)

t = int(input())
while t:
    t -= 1
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))

    nums.sort()
    prefix_sum = [0] * (n + 1)

    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + nums[i]

    max_sum = 0


    for i in range(k + 1):
        mins = prefix_sum[2 * i]
        maxes = prefix_sum[n] - prefix_sum[n - (k - i)]
        remaining_sum = prefix_sum[n] - mins - maxes

        max_sum = max(max_sum, remaining_sum)

    print(max_sum)
