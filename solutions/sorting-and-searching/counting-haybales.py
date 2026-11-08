from bisect import bisect_left, bisect_right

bale_num, query_num = map(int, input().split())
haybales = sorted(map(int, input().split()))

ans = []
for _ in range(query_num):
    start, end = map(int, input().split())
    left = bisect_left(haybales, start)
    right = bisect_right(haybales, end)
    ans.append(right - left)

print("\n".join(map(str, ans)))
