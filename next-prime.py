import sys

input = sys.stdin.read


def is_prime(n):
    if n < 2:
        return False
    for p in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]:
        if n % p == 0:
            return n == p
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    # For n < 2^64, these bases are deterministic
    for a in [2, 3, 5, 7, 11]:
        if a >= n:
            continue
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True


def next_prime(n):
    if n <= 2:
        return 2 if n < 2 else 3
    n += 1 if n % 2 == 0 else 2  # start from next odd
    while True:
        if is_prime(n):
            return n
        n += 2  # only odd numbers


data = input().split()
t = int(data[0])
queries = list(map(int, data[1:]))

for n in queries:
    print(next_prime(n))
