def solve():
    N, M, K = map(int, input().split())

    INF = float("inf")
    dist = [[INF] * N for _ in range(N)]

    for i in range(N):
        dist[i][i] = 0

    for _ in range(M):
        u, v, w = map(int, input().split())
        dist[u][v] = min(dist[u][v], w)
        dist[v][u] = min(dist[v][u], w)

    for k in range(N):
        for i in range(N):
            for j in range(N):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    def is_possible(D):
        covered = [False] * N
        used = 0
        remaining = set(range(N))

        while remaining and used < K:
            best = -1
            best_cov = set()

            for i in range(N):
                cov = set(j for j in remaining if dist[i][j] <= D)
                if len(cov) > len(best_cov):
                    best_cov = cov
                    best = i

            if not best_cov:
                return False

            remaining -= best_cov
            used += 1

        return len(remaining) == 0

    low, high = 0, max(max(row) for row in dist if max(row) < INF)

    result = -1
    while low <= high:
        mid = (low + high) // 2
        if is_possible(mid):
            result = mid
            high = mid - 1
        else:
            low = mid + 1

    print(result)


solve()