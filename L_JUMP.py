def explore(i, j, n, board, dp):
    if i >= n or j >= n:
        return 0
    if i == n - 1 and j == n - 1:
        return 1
    if board[i][j] == 0:
        return 0

    if dp[i][j] != -1:
        return dp[i][j]

    dp[i][j] = 0
    if i + board[i][j] < n:
        dp[i][j] = dp[i][j] + explore(i + board[i][j], j, n, board, dp)
    if j + board[i][j] < n:
        dp[i][j] = dp[i][j] + explore(i, j + board[i][j], n, board, dp)
    return dp[i][j]


n = int(input())
board = []
for _ in range(n):
    row = list(map(int, input().split()))
    board.append(row)

dp = [[-1] * n for _ in range(n)]
print(explore(0, 0, n, board, dp))
