import math
n = int(input())
while n:
    coords = []
    for i in range(2*n):
        inp = input().split()
        coords.append((int(inp[1]), int(inp[2])))

    total_cost = 0
    st = set()
    for i in range(2*n):
        if i in st: continue
        st.add(i)
        cost = float("inf")
        min_cost_index = 0
        for j in range(2*n):
            if j in st: continue
            if math.dist(coords[i], coords[j]) < cost:
                cost = math.dist(coords[i], coords[j])
                min_cost_index = j
        total_cost += cost
        st.add(min_cost_index)

    print(total_cost)
    n = int(input())
