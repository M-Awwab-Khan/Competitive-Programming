while True:
    try:
        line = input()
        if not line:  # Break if input is empty
            break
        n, s = map(int, line.split())

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

    except EOFError:  # Break if EOF is encountered
        break
