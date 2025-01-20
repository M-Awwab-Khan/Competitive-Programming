rows, cols = map(int, input().split())
board = [list(input()) for _ in range(rows)]

#is valid

def is_valid(row, col):
    return 0 <= row < rows and 0 <= col < cols

def main(rows, cols, board):
    for row in range(rows):
        for col in range(cols):
            # check if this entire grid is correct or not
            if board[row][col] == ".":

                for dr in range(-1, 2):
                    for dc in range(-1, 2):
                        if is_valid(row + dr, col + dc) and board[row + dr][col + dc] == "*":
                            print("NO")
                            return
            #it means there is a number
            elif board[row][col].isdigit():
                count = 0
                for dr in range(-1, 2):
                    for dc in range(-1, 2):
                        if is_valid(row + dr, col + dc) and board[row + dr][col + dc] == "*":
                            count += 1
                if count != int(board[row][col]):
                    print("NO")
                    return
    print("YES")

main(rows, cols, board)
