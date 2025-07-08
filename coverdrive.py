import math
n, r = map(float, input().split())

n = int(n)

coords = []
for i in range(n):
    x, y = map(float, input().split())
    coords.append((x, y))

intervals = []
for i in range(n):
    x, y = coords[i]
    d = math.hypot(x, y)

    if d <= r:
        print("0.000000")
        exit();

    theta = math.degrees(math.atan2(y, x))
    if theta < 0:
        theta += 360

    alpha = math.degrees(math.asin(r / d))
    s = theta - alpha
    e = theta + alpha

    if s < 0: s += 360
    if e > 360: e -= 360

    if s <= e: intervals.append((s, e))
    else:
        intervals.append((s, 360))
        intervals.append((0, e))

if not intervals:
    print("360.000000")
else:
    intervals.sort()
    m = []
    cs, ce = intervals[0]
    for start, end in intervals[1:]:
        if start <= ce :  
            ce = max(ce , end)
        else:
            m.append((cs, ce))
            cs, ce = start, end
    
    m.append((cs, ce))
    
    max_gap = 0
    for i in range(len(m)):
        start, end = m[i]
        next_start, next_end = m[(i + 1) % len(m)]
        
        gap = (next_start - end) % 360
        max_gap = max(max_gap, gap)

    print(f"{max_gap:.6f}")
    