bestValue = 0


def dfs(nums):
    global bestValue

    if len(nums) == 1:
        if nums[0] <= 24:
            bestValue = max(bestValue, nums[0])

    for i in range(len(nums)):
        for j in range(len(nums)):
            if i == j:
                continue

            nextnums = []
            for k in range(len(nums)):
                if k != i and k != j:
                    nextnums.append(nums[k])

            # try addition
            nextnums.append(nums[i] + nums[j])
            dfs(nextnums)
            nextnums.pop()

            # t try subtraction
            nextnums.append(nums[i] - nums[j])
            dfs(nextnums)
            nextnums.pop()

            # try multiplication
            nextnums.append(nums[i] * nums[j])
            dfs(nextnums)
            nextnums.pop()

            # try division
            if nums[j] != 0 and nums[i] % nums[j] == 0:
                nextnums.append(nums[i] // nums[j])
                dfs(nextnums)
                nextnums.pop()


def solve():
    global bestValue
    bestValue = -100000
    nums = [int(input()) for _ in range(4)]

    dfs(nums)

    print(bestValue)


if __name__ == "__main__":
    t = int(input())
    while t:
        t -= 1
        solve()
