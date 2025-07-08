# import re

# s = input().strip().lower()
# p= input().strip().lower()

# p= p.replace("?", ".")

# matches = [m.start() for m in re.finditer(p, s)]

# print(len(matches))
# print(*matches)

if __name__ == "__main__":
    s = input().strip().lower()
    p = input().strip().lower()
    res = []
    p_len = len(p)

    lps = [0] * p_len
    j = 0
    for i in range(1, p_len):
        while j > 0 and p[i] != p[j] and p[i] != "?" and p[j] != "?":
            j = lps[j - 1]
        if p[i] == p[j] or p[i] == "?" or p[j] == "?":
            j += 1
            lps[i] = j

    j = 0
    for i in range(len(s)):
        while j > 0 and p[j] != "?" and s[i] != p[j]:
            j = lps[j - 1]
        if p[j] == "?" or s[i] == p[j]:
            j += 1
            if j == p_len:
                res.append(i - p_len + 1)
                j = lps[j - 1]

    print(len(res))
    print(" ".join(str(x) for x in res))