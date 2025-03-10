s = input()
n = len(s)

flag = True
for i in range(1, n + 1):
    if (i % 2 == 1 and s[i - 1].isupper()) or (i % 2 == 0 and s[i - 1].islower()):
        flag = False
        break

print("Yes" if flag else "No")
