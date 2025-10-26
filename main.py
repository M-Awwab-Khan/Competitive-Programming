t = 1


def solve():
    n = int(input())
    lst = list(map(int, input().split()))

    lst.sort()
    for i in lst:
        print(i, end=" ")


while t:
    solve()

    t -= 1
