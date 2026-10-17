t = int(input())
for i in range(t):
    s = input()
    if s == "P=NP":
        print("skipped")
    else:
        print(eval(s))
