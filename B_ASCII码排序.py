s = " "
while s:
    try:
        s = input()
    except EOFError:
        exit()
    lst = []
    for char in s:
        lst.append(ord(char))
        lst.sort()

    print(*[chr(i) for i in lst], end=" ")
    print()
