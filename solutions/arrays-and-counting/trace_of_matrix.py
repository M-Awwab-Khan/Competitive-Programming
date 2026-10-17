t = int(input())

while t:
    t -= 1
    n = int(input())

    mat = [list(map(int, input().split())) for _ in range(n)]

    prefix_mat = [[0] * n for _ in range(n)]

    for i in range(n):
        prefix_mat[0][i] = mat[0][i]
        prefix_mat[i][0] = mat[i][0]

    for i in range(1, n):
        for j in range(1, n):
            prefix_mat[i][j] = mat[i][j] + prefix_mat[i-1][j-1]

    mx = 0
    for i in range(n):
        mx = max(prefix_mat[-1][i], prefix_mat[i][-1], mx)

    print(mx)
