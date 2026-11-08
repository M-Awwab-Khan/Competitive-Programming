from collections import defaultdict

t = int(input())
while t:
    t -= 1
    n = int(input())
    a = list(map(int, input().split()))

    ans = 0
    for k in range(2, n):
        hm = defaultdict(int)
        # preprocess first k elements
        for i in range(k):
            ans += hm[a[i]]
            hm[a[i]] += 1

        for i in range(k, n):
            hm[a[i - k]] -= 1
            ans += hm[a[i]]
            hm[a[i]] += 1
    print(ans)
