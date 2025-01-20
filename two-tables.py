t = int(input())
while t:
    t -= 1

    W, H = map(int, input().split())
    x1, y1, x2, y2 = map(int, input().split())
    w, h = map(int, input().split())


    ans = float("inf")
    if x2 - x1 + w > W and y2 - y1 + h > H:
        print(-1)
        continue

    if x2 - x1 + w <= W:
        ans = min(ans, max(0, w - x1), max(0, w - (W - x2)))

    if y2 - y1 + h <= H:
        ans = min(ans, max(0, h - y1), max(0, h - (H - y2)))

    ans = 0 if ans == float("inf") else ans

    print(f"{ans:.6f}")
