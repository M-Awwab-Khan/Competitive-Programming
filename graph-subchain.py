n = int(input())
vertices = []
while len(vertices) != n:
    s = input()
    if not s: break
    vertices.extend(list(map(int, s.split())))



# sub_chain = []
# hm = {}


# for i, vertex in enumerate(vertices):
#     if vertex not in hm:
#         hm[vertex] = i
#         sub_chain.append(vertex)
#     else:
#         while sub_chain and sub_chain[-1] != vertex:
#             sub_chain.pop()

# for v in sub_chain:
#     print(v, end=" ")
from collections import defaultdict, deque
adj_list = defaultdict(list)

# 1 2 7 3 2 8 4 8 5

for i in range(len(vertices) - 1):
    adj_list[vertices[i]].append(vertices[i+1])

def bfs():
    # edge case
    if n - 1 == len(adj_list):
        return [vertices[0]]

    q = deque()
    visited = set()
    path = {v: None for v in vertices}
    q.append(vertices[0])
    visited.add(vertices[0])

    while q:
        curr = q.popleft()
        if curr == vertices[-1]: break

        for child in adj_list[curr]:
            if child not in visited:
                q.append(child)
                visited.add(child)
                path[child] = curr

    sub_chain = []
    curr = vertices[-1]
    while path[curr]:
        sub_chain.append(curr)
        curr = path[curr]

    sub_chain = [vertices[0]] + sub_chain[::-1]
    return sub_chain


x = bfs()
for i in x: print(i, end=" ")
