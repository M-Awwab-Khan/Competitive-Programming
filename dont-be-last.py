COW_NUM = 7

raw = {}
for _ in range(int(input())):
    name, amt = input().split()
    amt = int(amt)
    if name not in raw:
        raw[name] = 0
    raw[name] += amt

cows = [(amt, name) for name, amt in raw.items()]
cows.sort()

ind = 0
if len(cows) == COW_NUM:
    while ind < len(cows) and cows[ind][0] == cows[0][0]:
        ind += 1

if ind < len(cows) and (ind + 1 == len(cows) or cows[ind][0] != cows[ind + 1][0]):
    print(cows[ind][1])
else:
    print("Tie")
