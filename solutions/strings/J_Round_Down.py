s = input()

i = s.find(".")
if i == -1:
    print(s)
else:
    print(s[:i])
