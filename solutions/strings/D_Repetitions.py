s = input()

curr = 1
ans = 1

for i in range(1, len(s)):
    if s[i] == s[i - 1]:
        curr += 1
    else:
        curr = 1
    ans = max(ans, curr)

print(ans)
