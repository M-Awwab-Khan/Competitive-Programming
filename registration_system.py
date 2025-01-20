from collections import defaultdict
hm = defaultdict(int)
t = int(input())
while t:
    t -= 1
    s = input()
    if s in hm:
        print(s + str(hm[s]))
    else:
        print("OK")
    hm[s] += 1
