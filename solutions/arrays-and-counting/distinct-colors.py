t = int(input())
while t:
    t -= 1
    n = int(input())
    nums = list(map(int, input().split()))
    print(max(nums))
