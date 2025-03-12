import math
from collections import defaultdict


def merge_intervals(intervals):
    if not intervals:
        return []
    sorted_intervals = sorted(intervals)
    merged = [sorted_intervals[0]]
    for current in sorted_intervals[1:]:
        last = merged[-1]
        if current[0] <= last[1] + 1:
            merged[-1] = (last[0], max(last[1], current[1]))
        else:
            merged.append(current)
    return merged


def solve():
    import sys

    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n, m = int(input[ptr]), int(input[ptr + 1])
        ptr += 2
        x = list(map(int, input[ptr : ptr + n]))
        ptr += n
        r = list(map(int, input[ptr : ptr + n]))
        ptr += n

        y0_intervals = []
        for i in range(n):
            xi = x[i]
            ri = r[i]
            start = xi - ri
            end = xi + ri
            y0_intervals.append((start, end))
        merged_y0 = merge_intervals(y0_intervals)
        ans = 0
        for s, e in merged_y0:
            ans += e - s + 1

        y_dict = defaultdict(list)
        for i in range(n):
            xi = x[i]
            ri = r[i]
            for y in range(1, ri + 1):
                y_sq = y * y
                r_sq = ri * ri
                if y_sq > r_sq:
                    dx = 0
                    break
                else:
                    dx = math.isqrt(r_sq - y_sq)
                start = xi - dx
                end = xi + dx
                if start <= end:
                    y_dict[y].append((start, end))

        for y in y_dict:
            intervals = y_dict[y]
            merged = merge_intervals(intervals)
            total = 0
            for s, e in merged:
                total += e - s + 1
            ans += 2 * total

        print(ans)


if __name__ == "__main__":
    solve()
