t = int(input())
sizes = []
while t > 0:
    sizes.append(list(map(int, input().split())))
    t -= 1


def print_matrix(mat):
    for row in mat:
        print(" ".join(row))

for (n, m) in sizes:
    default = [['1', '0'],
               ['0', '1']]

    r, c = 2, 2
    while c < m:
        copyfrom = 1 if c % 2 == 0 else 3
        default[0].append(default[0][c-copyfrom])
        default[1].append(default[1][c-copyfrom])
        c += 1

    while r < n:
        copyfrom = 1 if r % 2 == 0 else 3
        default.append(default[r - copyfrom])
        r += 1

    print_matrix(default)
