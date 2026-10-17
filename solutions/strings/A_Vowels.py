s = input()

v = "aeiou"
ans = 0
for i in s:
    if i in v:
        ans += 1

print(ans)
