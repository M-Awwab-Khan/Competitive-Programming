n, k = map(int, input().split())
x = list(map(int, input().split()))


def can_divide(mid):
    csum = 0
    count = 1
    for num in x:
        if csum + num > mid:
            count += 1
            csum = num

            if count > k:
                return False
        else:
            csum += num
    return True


l = max(x)
r = sum(x)

while l < r:
    mid = (l + r) // 2
    if can_divide(mid):
        r = mid
    else:
        l = mid + 1

print(l)
