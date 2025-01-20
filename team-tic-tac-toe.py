def tic_tac_toe():
    board = [input() for _ in range(3)]
    lines = []

    # Add rows
    lines.extend(board)

    # Add columns
    for col in range(3):
        lines.append("".join([board[row][col] for row in range(3)]))

    # Add diagonals
    lines.append("".join([board[i][i] for i in range(3)]))         # Top-left to bottom-right
    lines.append("".join([board[i][2 - i] for i in range(3)]))     # Top-right to bottom-left

    # Sets to store winners
    individual_winners = set()
    team_winners = set()

    # Check each line
    for line in lines:
        unique_cows = set(line)
        if len(unique_cows) == 1:
            # Single cow wins
            individual_winners.add(line[0])
        elif len(unique_cows) == 2:
            # Two cows team up
            cow1, cow2 = unique_cows
            if line.count(cow1) > 0 and line.count(cow2) > 0:
                team_winners.add(tuple(sorted(unique_cows)))

    # Output the results
    print(len(individual_winners))
    print(len(team_winners))

tic_tac_toe()
