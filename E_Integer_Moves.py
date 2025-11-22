t = int(input().strip())
from math import hypot

for _ in range(t):
    a, b = map(int, input().strip().split())
    x = hypot(a, b)
    if a == 0 and b == 0:
        print(0)
    elif a == 0 or b == 0:
        print(1)
    elif x % 1 != 0:
        # print(x)
        print(2)
    else:
        print(1)
