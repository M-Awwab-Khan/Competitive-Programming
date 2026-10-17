a = input()
b = input()

# count = 0
# for i in range(len(a)):
#     if (a[:i] + a[i+1:]) == b:
#         count += 1
#         indices.append(f"{i + 1}")

# print(count)
# print(' '.join(indices))

def prefix_len(s1, s2, l2):
    i = 0
    while i < l2 and s1[i] == s2[i]:
        i += 1
    return i

def suffix_len(s1, s2, l1):
    count = 0
    i = l1 - 1
    while i > 0 and s1[i] == s2[i-1]:
        count += 1
        i -= 1
    return count

def solve():
    l1 = len(a)
    l2 = len(b)
    pl = prefix_len(a, b, l2)
    sl = suffix_len(a, b, l1)

    total = (pl + 1) - (l1 - sl) + 1
    total = max(total, 0)

    print(total)
    for i in range(total):
        print(i + l1 - sl, end=" ")

solve()
