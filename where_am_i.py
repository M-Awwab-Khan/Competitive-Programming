n = int(input())
s = input()

for k in range(n - 1):
    st = set()
    for i in range(n - k + 1):
        sub = s[i:i + k]
        if sub in st:
            break
        st.add(sub)
    else:
        print(k)
        break
