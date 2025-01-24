from collections import defaultdict

t = int(input())
while t:
    t -= 1

    n, l, r = map(int, input().split())
    socks = list(map(int, input().split()))

    left = socks[:l]
    right = socks[l:]

    left_count = defaultdict(int)
    right_count = defaultdict(int)

    for color in left:
        left_count[color] += 1
    for color in right:
        right_count[color] += 1

    # Step 1: Pair as many as possible without changes
    for color in set(left_count.keys()) & set(right_count.keys()):
        paired = min(left_count[color], right_count[color])
        left_count[color] -= paired
        right_count[color] -= paired

    cost = 0
    for color, count in left_count.items():
        if count % 2 == 0:
            left_count[color] = 0
            cost += count // 2
        else:
            left_count[color] = 1
            cost += count // 2

    for color, count in right_count.items():
        print(color, count)
        if count % 2 == 0:
            right_count[color] = 0
            cost += count // 2
        else:
            right_count[color] = 1
            cost += count // 2

    print("cost after paring", cost)

    # Step 2: Pair the remaining socks
    remaining_left = []
    remaining_right = []
    for color, count in left_count.items():
        remaining_left.extend([color] * count)
    for color, count in right_count.items():
        remaining_right.extend([color] * count)

    print("remaining_left", remaining_left)
    print("remaining_right", remaining_right)
    cost += abs(len(remaining_left) - len(remaining_right)) // 2
    print("cost after pairing remaining", cost)
    cost += (len(remaining_left) + len(remaining_right)) // 2
    print(cost)
