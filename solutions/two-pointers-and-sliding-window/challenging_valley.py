t = int(input())
while t:
    t -= 1

    n = int(input())
    nums = list(map(int, input().split()))

    count = 0
    l = r = 0
    while r < n:
        c1 = c2 = False
        if nums[l] == nums[r]:
            while r < n-1 and nums[r+1] == nums[r]:
                r += 1
            if l == 0:
                c1 = True
            else:
                c1 = nums[l-1] > nums[l]
            if r == n - 1:
                c2 = True
            else:
                c2 = nums[r + 1] > nums[r]
            if c1 and c2:
                count += 1
            else:
                l = r + 1
        else:
            l = r + 1
        r += 1

    print("YES" if count == 1 else "NO")
