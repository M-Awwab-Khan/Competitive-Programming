r, c = map(int, input().split())
board = []
for _ in range(r):
    board.append(input())

directions = [(-1, -1), (0, -1), (1, -1),
              (-1, 0),          (1, 0),
              (-1, 1), (0, 1), (1, 1)]

def isValid(i, j):
    return 0 <= i < r and 0 <= j < c

def validate():
    for i in range(r):
        for j in range(c):
            cell = board[i][j]

            if cell.isdigit():
                count = 0
                for (dr, dc) in directions:
                    nr = i + dr
                    nc = j + dc

                    if isValid(nr, nc) and board[nr][nc] == "*":
                        count += 1

                if count != int(cell):
                    print("NO")
                    return

            elif cell == ".":

                for (dr, dc) in directions:
                    nr = i + dr
                    nc = j + dc

                    if isValid(nr, nc) and board[nr][nc] == "*":
                        print("NO")
                        return

    print("YES")

validate()
