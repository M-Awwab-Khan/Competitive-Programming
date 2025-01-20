n = int(input())
mat = [list(map(int, input().split())) for _ in range(n)]

def rotate90(mat):
    return [[mat[n-1-j][i] for j in range(n)] for i in range(n)]

mat90 = rotate90(mat)
mat180 = rotate90(mat90)
mat270 = rotate90(mat180)

answer = [[int(mat[i][j] or mat90[i][j] or mat180[i][j] or mat270[i][j]) for j in range(n)] for i in range(n)]

for row in answer:
    for i in row:
        print(i, end=" ")
    print()
