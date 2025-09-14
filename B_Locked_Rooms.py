n = int(input())
a = "".join(list(map(str, input().split())))

i = a.find("1")
j = a.rfind("1")

print(j - i)
