import bisect
import sys


def main():
    input = sys.stdin.read().split()
    idx = 0
    t = int(input[idx])
    idx += 1
    for _ in range(t):
        n, m = int(input[idx]), int(input[idx + 1])
        idx += 2
        a = list(map(int, input[idx : idx + m]))
        idx += m

        a_sorted = sorted(a)
        total = 0

        for x in range(1, n):
            k1 = x
            k2 = n - x

            cnt_x = m - bisect.bisect_left(a_sorted, k1)
            cnt_y = m - bisect.bisect_left(a_sorted, k2)

            max_k = max(k1, k2)
            cnt_both = m - bisect.bisect_left(a_sorted, max_k)

            contribution = cnt_x * cnt_y - cnt_both
            total += contribution

        print(total)


if __name__ == "__main__":
    main()
