t = int(input())
while t:
    t -= 1
    n = int(input())
    planks = list(map(int, input().split()))

    planks.sort()
    base = min(planks[-1], planks[-2])

    count = 0
    for i in range(n - 2):
        if count == base - 1:
            break

        count += 1

    print(count)

# def max_ladder_steps():
#     t = int(input())
#     results = []
#     for _ in range(t):
#         n = int(input())
#         planks = input().split()
#         for i in range(len(planks)):
#             planks[i] = int(planks[i])
#         planks.sort()
#         k = 0
#         for i in range(n):
#             if planks[i] >= n - i:
#                 k = n - i
#                 break
#         results.append(k)

#     for res in results:
#         print(res)

# max_ladder_steps()
