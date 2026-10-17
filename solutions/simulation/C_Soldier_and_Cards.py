n = int(input())
first_line = list(map(int, input().split()))
k1, p1 = first_line[0], first_line[1:]
second_line = list(map(int, input().split()))
k2, p2 = second_line[0], second_line[1:]

p1.reverse()
p2.reverse()


fights = 0
outofbound = False
while not outofbound:
    if not p1:
        print(fights, 2)
        break
    if not p2:
        print(fights, 1)
        break

    if fights > 1000:
        outofbound = True

    top1 = p1.pop()
    top2 = p2.pop()
    fights += 1

    if top1 > top2:  # player 1 wins
        p1.insert(0, top2)
        p1.insert(0, top1)
    else:
        p2.insert(0, top1)
        p2.insert(0, top2)
else:
    print(-1)
