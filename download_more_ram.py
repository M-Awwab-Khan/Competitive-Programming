t = int(input())
while t:
    t -= 1
    n, k = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    nums = sorted(zip(a, b), key=lambda x: x[0])
    for consume, return_ in nums:
        if k < consume: break
        k += return_

    print(k)
