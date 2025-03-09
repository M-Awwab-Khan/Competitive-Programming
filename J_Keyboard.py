dir = input()
s = input()
shift = -1 if dir == "R" else 1

top = "qwertyuiop"
bottom = "asdfghjkl;"
left = "zxcvbnm,./"

for i in s:
    if i in top:
        print(top[top.index(i) + shift], end="")
    elif i in bottom:
        print(bottom[bottom.index(i) + shift], end="")
    elif i in left:
        print(left[left.index(i) + shift], end="")
    else:
        print(i, end="")
