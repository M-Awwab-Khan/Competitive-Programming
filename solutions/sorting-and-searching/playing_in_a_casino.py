t = int(input())
while t:
    t -= 1

    n, m = map(int, input().split())
    cards = [list(map(int, input().split())) for _ in range(n)]

    total = 0
    for col in range(m):
        sorted_col = sorted(cards[i][col] for i in range(n))

        prefix_sum = 0
        for i in range(n):
            total += i * sorted_col[i] - prefix_sum
            prefix_sum += sorted_col[i]


    print(total)
