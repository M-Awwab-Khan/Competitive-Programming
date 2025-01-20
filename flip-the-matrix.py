n = int(input())
A = [input().split() for _ in range(n)]
B = [input().split() for _ in range(n)]

def flipH(mat):
    return [row[::-1] for row in mat]

def flipV(mat):
    return mat[::-1]

if flipH(A) == B or flipV(A) == B:
    print(1)
else:
    print(0)
