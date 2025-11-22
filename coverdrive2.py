import math


def solve():
    n, r = input().split()
    n = int(n)
    r = float(r)

    xp, yp = map(float, input().split())

    drones = []
    for _ in range(n):
        x, y = map(float, input().split())
        drones.append((x, y))

    # The player's forward direction is assumed to be along +x axis.
    # The valid cone is angle ∈ [-90°, 90°].

    intervals = []

    for x, y in drones:
        # Translate drone relative to player
        dx = x - xp
        dy = y - yp

        d = math.hypot(dx, dy)

        # Drone covers all angles if it's too close
        if d <= r:
            print("0.00")
            return

        # Angle of drone from player
        theta = math.degrees(math.atan2(dy, dx))  # angle ∈ (-180, 180)

        # Cone only includes [-90, 90], so skip if drone is behind
        if theta < -90 or theta > 90:
            continue

        # Angular half-width covered by the drone
        alpha = math.degrees(math.asin(r / d))

        s = theta - alpha
        e = theta + alpha

        # Clip interval to cone limits
        s = max(s, -90)
        e = min(e, 90)

        if s <= e:
            intervals.append((s, e))

    # If no blocking intervals → entire 180° free
    if not intervals:
        print("180.00")
        return

    # Merge intervals
    intervals.sort()
    merged = []
    cs, ce = intervals[0]

    for s, e in intervals[1:]:
        if s <= ce:
            ce = max(ce, e)
        else:
            merged.append((cs, ce))
            cs, ce = s, e
    merged.append((cs, ce))

    # Compute maximum angular gap between merged intervals within [-90, 90]
    max_gap = 0
    start_angle = -90

    for s, e in merged:
        gap = s - start_angle
        max_gap = max(max_gap, gap)
        start_angle = e

    # Gap after last interval
    max_gap = max(max_gap, 90 - start_angle)

    # Output truncated to exactly 2 decimals
    print(f"{max_gap:.2f}")


t = int(input())
for _ in range(t):
    solve()
