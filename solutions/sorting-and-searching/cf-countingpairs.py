from bisect import bisect_left, bisect_right


def count_interesting_pairs(test_cases):
    results = []

    for t in test_cases:
        n, x, y, a = t
        S = sum(a)
        a.sort()

        count = 0
        for i in range(n):
            L = S - y - a[i]
            R = S - x - a[i]

            left_idx = bisect_left(a, L, i + 1)
            right_idx = bisect_right(a, R, i + 1)

            count += right_idx - left_idx

        results.append(count)

    return results


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    t = int(data[0])
    test_cases = []
    idx = 1
    for _ in range(t):
        n, x, y = map(int, data[idx : idx + 3])
        idx += 3
        a = list(map(int, data[idx : idx + n]))
        idx += n
        test_cases.append((n, x, y, a))

    results = count_interesting_pairs(test_cases)

    sys.stdout.write("\n".join(map(str, results)) + "\n")


if __name__ == "__main__":
    main()
