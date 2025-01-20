def max_total_height(n, h1, h2):
    #dp arrays
    dp1 = [0] * n
    dp2 = [0] * n
    dp1[0] = h1[0]
    dp2[0] = h2[0]

    max_dp1 = dp1[0]
    max_dp2 = dp2[0]

    for i in range(1, n):
        #max of other row + current height
        dp1[i] = max_dp2 + h1[i]
        dp2[i] = max_dp1 + h2[i]

        max_dp1 = max(max_dp1, dp1[i])
        max_dp2 = max(max_dp2, dp2[i])

    return max(max_dp1, max_dp2)

n = int(input())
h1 = list(map(int, input().split()))
h2 = list(map(int, input().split()))

print(max_total_height(n, h1, h2))
