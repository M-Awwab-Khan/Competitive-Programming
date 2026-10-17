s = input()
i = s.find("0")
if i == -1:
    print("1" * (len(s) - 1))
    exit()
print(s[:i] + s[i + 1 :])
