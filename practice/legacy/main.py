t = int(input())

while t:
    n = int(input())
    a = []
    for _ in range(n):
        a.append(input())
    a.reverse()
    print(" ".join(a))

    t -= 1
