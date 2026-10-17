t = int(input())
while t:
    t -= 1
    n = int(input())
    nums = list(map(int, input().split()))
    maxVal = max(nums)
    avg1 = (sum(nums) - maxVal) / (n - 1)
    result = maxVal + avg1
    print(f"{result:.6f}")
