def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        b = list(map(int, data[idx : idx + 2 * n]))
        idx += 2 * n
        # Sort b in non-decreasing order
        b.sort()
        # Split into S (even indices 1-based) and T (odd indices 1-based)
        S = []
        T = []
        for i in range(2 * n):
            if (i + 1) % 2 == 0:  # even indices (1-based)
                S.append(b[i])
            else:
                T.append(b[i])
        x = sum(S) - sum(T)
        # Interleave S and T to form the rest of the sequence
        a = [x]
        for s, t in zip(S, T):
            a.append(s)
            a.append(t)
        # Output the sequence a
        print(" ".join(map(str, a)))


if __name__ == "__main__":
    main()
