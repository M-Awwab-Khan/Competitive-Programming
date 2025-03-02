import math


def is_square(x):
    if x < 0:
        return False
    s = math.isqrt(x)
    return s * s == x


t = int(input())
for _ in range(t):
    n = int(input())
    total_sum = n * (n + 1) // 2
    if is_square(total_sum):
        print(-1)
    else:
        if n == 1:
            print(-1)
            continue
        perm = [2, 1]
        current_sum = 3
        i = 3
        while i <= n:
            s = current_sum + i
            if is_square(s):
                if i + 1 > n:
                    perm = [-1]
                    break
                perm.append(i + 1)
                perm.append(i)
                current_sum += (i + 1) + i
                i += 2
            else:
                perm.append(i)
                current_sum += i
                i += 1
        if len(perm) == n:
            print(" ".join(map(str, perm)))
        else:
            print(-1)
